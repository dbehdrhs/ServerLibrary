#include "stdafx.h"
#include "SessionManager.h"


SessionManager::SessionManager()
{
}


SessionManager::~SessionManager()
{
}

void SessionManager::Init()
{
	if (!sessionList_.empty())
	{
		Release();
	}

	maxCount_ = SESSION_CAPACITY;
	sessionCount_ = 0;
	sessionId_ = 1;
}

void SessionManager::Release()
{
	for (auto data : sessionList_)
	{
		data->CloseSocket();
		delete data;
	}

	sessionList_.clear();
}

bool SessionManager::AddSession()
{
	return false;
}

bool SessionManager::CloseSession(BaseSocket * session)
{
	return false;
}

BaseSocket * SessionManager::Session(int id)
{
	for (auto session : sessionList_)
	{
		if (session->ID() == id)
		{
			return session;
		}
	}

	cout << "[INFO] Not Found Session " << id << endl;
	return nullptr;
}
