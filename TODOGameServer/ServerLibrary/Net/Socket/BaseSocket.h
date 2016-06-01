#pragma once

class BaseSocket
{
public:
	BaseSocket();
	virtual ~BaseSocket();

	BaseSocket(int id);

	BOOL CreateSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = 0);

	string GetAddrToString();
	SOCKET& Socket() { return sock_; }
	SOCKADDR_IN& Addr() { return addr_; }
	int ID() { return id_; }

	void SetId(int id) { id_ = id; }
	void SetSocketOption();

	virtual void OnSend() = 0;
	virtual void OnRecv() = 0;

	virtual void OnAccept(SOCKET sock, SOCKADDR_IN addr);
	virtual void OnClose();
	
	bool CloseSocket();

	bool IsRoomJoin() { /*return (room : true ? false);*/ }

protected:
	SOCKET sock_;
	SOCKADDR_IN addr_;

	int id_;
};