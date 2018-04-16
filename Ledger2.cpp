//Ledger.cpp
//Author: Anjie Wang, Jiachen Wang
//This file implements a ledger process under the 2PC protocol.
//UDP message format: "C100"/"D250"/"Q","Y"/"N","C"/"A","20".

#include "PracticalSocket.h"
#include "UDPTools.h"
#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <chrono>
#include <string.h>
using namespace std;

//global constants and variables
const string SERVER="localhost";
const int MAX_LEDGER=5;

int balance;
unsigned short localPort;
string servPort[MAX_LEDGER];
int numLedger;
mutex mtx;

//Initialize()
void Initialize(int argc,char *argv[])
{
  if (argc<3 || argc>8) {
    cerr<<"Usage: "<<argv[0]
	<<"\n\t<LocalPort>\n"
	<<"\t<number of neighboring ledgers>\n"
	<<"\t<neighborPort(s)>\n"
	<<"\t[R]\n"
	<<"* max number of neighboring ledgers: "<<MAX_LEDGER-1<<"\n"
	<<"* R - ledger restarts after failure\n";
    exit(1);
  }
  
  localPort = atoi(argv[1]);
  UDPSocket sock(localPort);

  numLedger = atoi(argv[2]);
  for (int i=0;i<numLedger;i++) {
    servPort[i]=argv[i+3];
  }

   //to synthesis this process's data by asking other running processes 
  string last = argv[argc-1];
  if (last=="R") {
    int i=-1;
    string reply;

    do {
      i++;
      reply=send_recv("Q",SERVER,servPort[i],sock);
    } while ((reply=="Timeout" || reply=="Error") && i<numLedger-1);
      
    balance = atoi(reply.c_str());

  } else {
    balance = 0;
  }
}

//Participant()
void participant(UDPSocket &sock)
{
  for (;;) {
    //lock
    mtx.lock();
    
    //receive a message from a random other socket
    string recvMsg = recv(sock);
    
    if (recvMsg!="Timeout") {   

      //handle cases (like "C100:5000")
      //meaning that the message C100 comes from port 5000
      string type=recvMsg.substr(0,1);
      size_t loc=recvMsg.find(":");
      int num=atoi(recvMsg.substr(1,loc-1).c_str());
      string targetPort=recvMsg.substr(loc+1);
      string reply;
      
      //always answer yes to credit action
      if (type == "C") {
	reply = send_recv("Y",SERVER,targetPort,sock);
	if (reply=="C") {
	  balance+=num;
	}
	
      //answer yes to debit action unless there isn't enough balance left
      } else if (type == "D") {
	if (balance>=num) {
	  reply = send_recv("Y",SERVER,targetPort,sock);
	} else {
	  reply = send_recv("N",SERVER,targetPort,sock);
	}
	if (reply=="C") {
	  balance-=num;
	}
	
      //answer quering 
      } else if (type == "Q") {
	send(to_string(balance),SERVER,targetPort,sock);
      }
    }
    //unlock resources
    mtx.unlock();
  }
}

//coordinator()
void coordinator(UDPSocket &sock)
{
  for (;;) {
    cout<<"----------------------------------\n";
    cout<<"Request: ";
    string request;
    cin>>request;
    
    //lock
    mtx.lock();
    
    //handle
    string type = request.substr(0,1);
    size_t num = atoi(request.substr(1).c_str());
    string reply;

    //distribute credit action    
    if (type == "C") {
      bool vote=true;
      for (int i=0;i<numLedger;i++) {
	reply = send_recv(request,SERVER,servPort[i],sock);
	if (reply!="Y") {
	  vote=false;
	}
      }
      
      if (vote) {
	balance+=num;
	for (int i=0;i<numLedger;i++) {
	  send("C",SERVER,servPort[i],sock);
	}
	std::cout<<"Operation succeeds\n";
      } else {
	for (int i=0;i<numLedger;i++) {
	  send("A",SERVER,servPort[i],sock);
	}
	std::cout<<"Operation aborts\n";
      }
      
    //distribute debit action
    } else if (type == "D") {
      bool vote = balance>=num;
      for (int i=0;i<numLedger;i++) {
	reply = send_recv(request,SERVER,servPort[i],sock);
	if (reply!="Y") {
	  vote=false;
	}
      }
      
      if (vote) {
	balance-=num;
	for (int i=0;i<numLedger;i++) {
	  send("C",SERVER,servPort[i],sock);
	}
	std::cout<<"Operation succeeds\n";
      } else {
	for (int i=0;i<numLedger;i++) {
	  send("A",SERVER,servPort[i],sock);
	}
	std::cout<<"Operation aborts\n";
      }
      
    } else if (type == "Q") {
      bool vote = true;
      //distribute query question to every participant and collect answers
      for (int i=0;i<numLedger;i++) {
	reply = send_recv(request,SERVER,servPort[i],sock);
	if (reply!="Timeout" && reply!="Error" && reply != to_string(balance)) {
	  vote = false;
	}
      }
      
      if (vote) {
	std::cout<<"Cur Balance: "<<balance<<"\n";
      } else {
	std::cout<<"Operation encounters an error-"<<reply<<"\n";
      }
    }
    
    //unlock
    mtx.unlock();
  }
}

int main(int argc, char *argv[])
{
  cout<<"----------Ledger starting---------\n";
  Initialize(argc,argv);
  UDPSocket sock(localPort);
  
  cout<<"----------Ledger launched---------\n";
  cout<<"----------------------------------\n"
      <<"|              Help              |\n"
      <<"|         Credit: C100           |\n"
      <<"|         Debit:  D100           |\n"
      <<"|         Query:  Q              |\n"   
      <<"----------------------------------\n";

  thread t1(participant,ref(sock));
  thread t2(coordinator,ref(sock));
  t1.join();
  t2.join();
}
  
