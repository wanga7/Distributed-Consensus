#include "PracticalSocket.h"	// For UDPSocket and SocketException
#include "UDPTools.h"
#include <iostream>		// For cout and cerr
#include <cstdlib>		// For atoi()
#include <string.h>
//const int ECHOMAX = 255;	// Longest string to echo

int main(int argc, char *argv[])
{

  if (argc != 4) {
    cerr << "Usage: " << argv[0]
	 << " <Server> <ServPort> <LocalPort>\n";
    exit(1);
  }

    unsigned short localPort = atoi(argv[3]);	// First arg:  local port
    string servAddress = argv[1];
    string servPort = argv[2];
    
    try {
      /*
	UDPSocket sock(localPort);

	char echoBuffer[ECHOMAX];	// Buffer for echo string
	//char replyBuffer[ECHOMAX];
	string replyMsg;
	char* replyString;
	int recvMsgSize;	// Size of received message
	int replyMsgSize;
	string sourceAddress;	// Address of datagram source
	unsigned short sourcePort;	// Port of datagram source
      */
      string replyMsg;
	for (;;) {		// Run forever
	    // Block until receive message from a client
	  for (;;) {
	    string recvMsg = recv(localPort);
	    if (recvMsg!="Timeout") {
	      cout<<"Recv: "<<recvMsg<<endl;
	      break;
	    }
	  }
	  /*
	    recvMsgSize
		=
		sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress,
			      sourcePort);
	    if (recvMsgSize==-1) {
	      cout<<"recv timeout\n";
	      continue;
	    }
	    echoBuffer[recvMsgSize]='\0';
	    
	    cout << "Received: (" << sourceAddress << ":" <<
	      sourcePort << ") "<<echoBuffer
		<< endl;
	  */
	    cout<<"Reply: ";
	    cin>>replyMsg;
	    send(replyMsg,servAddress,servPort,localPort);
	    
	    //replyMsgSize = strlen(replyBuffer);
	    //cout<<"Reply message:"<<replyBuffer<<" | len="<<replyMsgSize<<endl;
	    //sock.sendTo(replyBuffer, replyMsgSize, sourceAddress,
	    //		sourcePort);
	}
    }
    catch(SocketException & e) {
	cerr << e.what() << endl;
	exit(1);
    }
    // NOT REACHED

    return 0;
}

//void recvMessage() {
  
