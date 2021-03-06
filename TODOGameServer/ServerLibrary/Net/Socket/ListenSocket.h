#pragma once
#include "BaseSocket.h"

class ListenSocket : public BaseSocket
{
public:
	ListenSocket();
	virtual ~ListenSocket();

	void CreateListenSocket(int af, int type, int protocol);

	BOOL Bind(int af);
	BOOL Listen();

	ClientSession* Accept();

	static DWORD WINAPI AcceptThread(LPVOID serverPtr);
};

