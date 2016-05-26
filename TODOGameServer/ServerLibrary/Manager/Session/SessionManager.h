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

	bool AddSession();
	bool CloseSession(BaseSocket* session);

	BaseSocket* Session(int id);

private:
	vector<BaseSocket*> sessionList_;

	int sessionCount_;
	int maxCount_;

	int sessionId_;
};

