#include "PracticalSocket.h"	// For UDPSocket and SocketException
#include "UDPTools.h"
#include <iostream>		// For cout and cerr
#include <cstdlib>		// For atoi()
#include <string.h>
using namespace std;

//const int ECHOMAX = 255;	// Longest string to echo

int main(int argc, char *argv[])
{
  if (argc != 4) {
    cerr << "Usage: " << argv[0]
	 << " <Server> <ServPort> <LocalPort>\n";
    exit(1);
  }
  string servAddress = argv[1];
  string servPort = argv[2];
  unsigned short localPort = atoi(argv[3]);
  cout<<"UDPEchoClient launched\n";
  string message,replyMsg;
  UDPSocket sock;
  for (;;) {
    char option;
    cin>>option;
    if (option=='q') {
      break;
    } else {
      cin>>message;
      replyMsg = send_recv(message,servAddress,servPort,localPort);
      cout<<"Reply: "<<replyMsg<<endl;
    }
  }
}
