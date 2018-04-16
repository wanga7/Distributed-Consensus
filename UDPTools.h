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
//send a message to another given port
void send(string msg,string servAddress,string servPort,UDPSocket &sock)
{
  unsigned short echoServPort = Socket::resolveService(servPort,"udp");

  try {
    char msgBuffer[ECHOMAX];
    for (int i=0;i<msg.length();i++) {
      msgBuffer[i]=msg[i];
    }

    // Send the string to the server
    sock.sendTo(msgBuffer, msg.length(), servAddress, echoServPort);

  }
  catch(SocketException & e) {
    cerr << e.what() << endl;
    exit(1);
  }
}

//recv()
//receive a message from any port
//return format:"message:sourcePort"
//return "Timeout" if timeout
string recv(UDPSocket &sock)
{
  try {
    char echoBuffer[ECHOMAX];
    string sourceAddress;
    unsigned short sourcePort;
    int recvMsgSize;

    //receive a message
    recvMsgSize = sock.recvFrom(echoBuffer, ECHOMAX, sourceAddress, sourcePort);

    if (recvMsgSize==-1) {
      return "Timeout";
    } else {
      echoBuffer[recvMsgSize]=':';
      string sourceStr=to_string(sourcePort);

      for (int i=0;i<sourceStr.length();i++) {
	echoBuffer[recvMsgSize+1+i]=sourceStr[i];
      }

      echoBuffer[recvMsgSize+1+sourceStr.length()]='\0';
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
//send a message to another port, and wait for the specific port to reply
//@returns "Timeout" - for message reply timeout
//"Error" - error during execution
//normal response message - otherwise
string send_recv(string msg,string servAddress,string servPort,UDPSocket &sock)
{
  unsigned short echoServPort = Socket::resolveService(servPort , "udp");

  try {
    char msgBuffer[ECHOMAX];
    for (int i=0;i<msg.length();i++) {
      msgBuffer[i]=msg[i];
    }

    // Send the string to the server
    sock.sendTo(msgBuffer, msg.length(), servAddress, echoServPort);

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

  }
  catch(SocketException & e) {
    cerr << e.what() << endl;
    exit(1);
  }
  return "Error";
}
