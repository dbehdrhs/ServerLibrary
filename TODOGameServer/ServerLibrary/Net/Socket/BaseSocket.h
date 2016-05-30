#pragma once

class BaseSocket
{
public:
	BaseSocket();
	virtual ~BaseSocket();

	BaseSocket(int id);

	BOOL CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);
	BOOL CloseSocket();

	string GetAddrToString();
	SOCKET& Socket() { return sock_; }
	SOCKADDR_IN& Addr() { return addr_; }
	int ID() { return id_; }

	void SetId(int id) { id_ = id; }

	virtual void OnRecv() = 0;

protected:
	SOCKET sock_;
	SOCKADDR_IN addr_;

	int id_;
};
