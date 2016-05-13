#pragma once
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

//
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

#include <iostream>

#include <array>

using namespace std;


// Util
#include "./Util/Type.h"
// TODO[1] : xml parsing 
// TODO[1] : Log : file, dump, print
// TODO[1] : ADO or ODBC
// TODO[1] : monitoring

// Network
#include "./Net/wsa.h"


// DB