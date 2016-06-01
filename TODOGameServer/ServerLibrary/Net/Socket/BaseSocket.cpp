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

BaseSocket::BaseSocket(int id)
{
	id_ = id;
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

bool BaseSocket::CloseSocket()
{
	if (sock_ != INVALID_SOCKET)
	{
		// TODO : Check read and write stream. shutdown();
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

void BaseSocket::OnAccept(SOCKET sock, SOCKADDR_IN addr)
{
	sock_ = sock;
	addr_ = addr;
}

void BaseSocket::OnClose()
{
	CloseSocket();
}

void BaseSocket::SetSocketOption()
{
}
