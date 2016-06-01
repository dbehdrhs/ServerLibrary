#pragma once

enum SERVER_STATUS
{
	SERVER_INITIALIZE,
	SERVER_RUN,
	SERVER_STOP,
};

class BaseServer
{
public:
	BaseServer();
	virtual ~BaseServer();

	bool Init(xml_t config);
	void Release();

	//virtual bool OnAccept() = 0;
	virtual bool OnRecv() = 0;

	SERVER_STATUS& status() { return status_; }
	SOCKET& ListenSocket() { return listenSocket_; }

protected:
	SERVER_STATUS status_;

	SOCKET listenSocket_;
	int port_;
	char ip_[16];

	int workerThreadCount_;
};

