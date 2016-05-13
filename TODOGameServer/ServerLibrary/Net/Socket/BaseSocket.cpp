#include "stdafx.h"
#include "BaseSocket.h"

BaseSocket::BaseSocket()
{
	ZeroMemory(&addr_, sizeof(SOCKADDR_IN));
}

BaseSocket::~BaseSocket()
{
	CloseSocket();
}

BOOL BaseSocket::CreateSocket(int af, int type, int protocol)
{
	sock_ = socket(af, type, protocol);
	if (sock_ == INVALID_SOCKET)
	{
		cout << "[ERROR] Create Socket Failed" << endl;
		return FALSE;
	}

	return TRUE;
}

BOOL BaseSocket::CloseSocket()
{
	if (sock_ != INVALID_SOCKET)
	{
		closesocket(sock_);
		return TRUE;
	}
		
	return FALSE;
}

string BaseSocket::GetAddrToString()
{
	array<char, SIZE_64> ip;

	inet_ntop(addr_.sin_family, &addr_, ip.data(), ip.size());

	return ip.data();
}
