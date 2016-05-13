#pragma once

class BaseSocket
{
public:
	BaseSocket();
	virtual ~BaseSocket();

	BOOL CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);
	BOOL CloseSocket();

	string GetAddrToString();
	SOCKET& GetSocket() { return sock_; }
	SOCKADDR_IN& GetAddr() { return addr_; }

	virtual void OnRecv() = 0;

protected:
	SOCKET sock_;
	SOCKADDR_IN addr_;
};
