#pragma once

#include "stdafx.h"
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

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
	AcceptThread(int port) //also needs selector and connectionList
	{

	}

};