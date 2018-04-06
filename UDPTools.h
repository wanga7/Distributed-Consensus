//UDPTools.h
//Author: Anjie Wang
//This file declares and implements some helper functions for UDP communication

#include "PracticalSocket.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;

const int ECHOMAX = 255;

//send()
//send a message to another port
void send(string msg,string servAddress,string servPort,
	  unsigned short localPort)
{
  unsigned short echoServPort = Socket::resolveService(servPort,"udp");

  try {
    char msgBuffer[ECHOMAX];
    for (int i=0;i<msg.length();i++) {
      msgBuffer[i]=msg[i];
    }
    int msgBufferLen = strlen(msgBuffer);
    
    UDPSocket sock(localPort);

    // Send the string to the server
    sock.sendTo(msgBuffer, msg.length(), servAddress, echoServPort);

    // Destructor closes the socket
  }
  catch(SocketException & e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

//recv()
//receive a message from any port
//return "Timeout" if timeout
string recv(unsigned short localPort)
{
  try {
    UDPSocket sock(localPort);

    char echoBuffer[ECHOMAX];
    string sourceAddress;
    unsigned short sourcePort;
    int recvMsgSize;

    recvMsgSize = sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress, sourcePort);
    if (recvMsgSize==-1) {
      return "Timeout";
    } else {
      echoBuffer[recvMsgSize]='\0';
      return echoBuffer;
    }
  }
  catch(SocketException & e) {
	cerr << e.what() << endl;
	exit(1);
  }
  return "Error";
}

//send_recv()
//send a message to another port, and wait for reply
//a timer is set for the time of the reply
//@returns "Timeout" - timeout for the reply message
//         "Error" - error during executing the function
//         normal response message - otherwise
string send_recv(string echoString,string servAddress,string servPort,
		 unsigned short localPort) {
  unsigned short echoServPort
    = Socket::resolveService(servPort , "udp");

  try {
    char msgBuffer[ECHOMAX];
    for (int i=0;i<echoString.length();i++) {
      msgBuffer[i]=echoString[i];
    }
    int msgBufferLen = strlen(msgBuffer);
    
    UDPSocket sock(localPort);

    // Send the string to the server
    sock.sendTo(msgBuffer, echoString.length(), servAddress, echoServPort);

    // Receive a response
    char echoBuffer[ECHOMAX + 1];	// Buffer for echoed string + \0
    int respStringLen;	// Length of received response
    respStringLen = sock.recv(echoBuffer, ECHOMAX);
    if (respStringLen==-1) {
      return "Timeout";
    } else {
      echoBuffer[respStringLen] = '\0';	// Terminate the string!
      return echoBuffer;
    }
    // Destructor closes the socket
  }
  catch(SocketException & e) {
    cerr << e.what() << endl;
    exit(1);
  }
  return "Error";
}
