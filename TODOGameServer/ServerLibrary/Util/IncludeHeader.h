#pragma once
#include "stdafx.h"

#pragma comment(lib, "ws2_32.lib")

//
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>

#include <thread>
#include <mutex>

#include <map>
//#include <hash_map>
#include <array>
#include <list>
#include <vector>

#include <chrono>

#include <iostream>


using namespace std;


// Util
#include "./Util/tinyXml/tinyxml.h"
#include "ShutDown.h"
// TODO[2] : Setting(SERVER:ip, port, MAX_CONNECT_COUNT)

#include "./Util/Type.h"
#include "./Util/Singleton.h"

#include "config.h"
// TODO[0] : xml parsing 
// TODO[0] : Log : file, dump, print
// TODO[0] : ADO or ODBC
// TODO[0] : monitoring

// TODO[1] : ThreadManager
// TODO[1] : Thread
// TODO[1] : Lock, LockScope



// Network
#include "./Net/wsa.h"
#include "./Net/Socket/ClientSession.h"
#include "./Manager/Session/SessionManager.h"
// TODO[2] : Packet

// TODO[2] : BaseServer
// TODO[2] : Lobby
// TODO[2] : Game




// DB