#pragma once

#include "stdafx.h"
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

/// This is a subclass? of thread to be used for accepting 
/// incoming connections.
class AcceptThread : std::thread
{
private:
	// socket channel?
	// selector?
	// connectionList?
public:
	/*
	A lot of the code here (so far all) is from
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms740632(v=vs.85).aspx
	*/
	AcceptThread(int port) //also needs selector and connectionList
	{
		#define DEFAULT_PORT "27015" // it must be done this way for some reason
	
		WSADATA wsaData; // WSA - WinSockApplication Data from winsock2.h
		struct addrinfo *result = NULL, *ptr = NULL, hints; // make addrinfo with result and ptr, and hints?
		int iResult; // return from WSAStartup

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); // Startup service using this function
		if (iResult != 0) // Did not succeed
		{
			printf("WSAStartup failed: %d\n", iResult); // Give the result
			assert(iResult != 0); // Crash out gracefully
		}

		// Create a socket for the server

		// All this stuff is defined up in winsock2.h
		// Legitimately I don't really know what most of this means
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the local address and port to be used by the server
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0)
		{
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			assert(iResult != 0);
		}

		// Make the socket object

		SOCKET ListenSocket = INVALID_SOCKET; // here is our first socket object
		ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol); // attempt to get a valid socket object assigned to this reference

		// Make sure we got a valid socket
		if (ListenSocket == INVALID_SOCKET) 
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			assert(ListenSocket == INVALID_SOCKET);
		}

		// Setup the TCP listening socket
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			assert(iResult == SOCKET_ERROR);
		}
	}

};