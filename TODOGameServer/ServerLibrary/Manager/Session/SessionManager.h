#pragma once
#include "stdafx.h"

#define SESSION_CAPACITY	(5000)

class SessionManager :	public Singleton<SessionManager>
{
public:
	SessionManager();
	virtual ~SessionManager();

	void Init();
	void Release();

	bool AddSession(BaseSocket* session);
	bool CloseSession(BaseSocket* session);

	BaseSocket* Session(int id);
	int Count() { return sessionCount_; }

private:
	int CreateSessionId();

private:
	list<BaseSocket*> sessionList_;
	int maxCount_;
	int sessionCount_;
	int sessionId_;
};

