#include "stdafx.h"
#include "SessionManager.h"


SessionManager::SessionManager()
 :lock_("SessionManager")
{
	
	Init();
}

SessionManager::~SessionManager()
{
	Release();
}

void SessionManager::Init()
{
	if (!sessionList_.empty())
	{
		Release();
	}

	maxCount_ = SESSION_CAPACITY;
	sessionId_ = 1;
	sessionCount_ = 0;

	//
	for (int i = 0; i < SESSION_CAPACITY; i++)
	{
		IocpSession* session = new IocpSession;
		AddSession(session);
	}
}

void SessionManager::Release()
{
	for(auto iter : sessionList_)
	{
		iter->OnClose();
	}

	sessionList_.clear();
}

bool SessionManager::AddSession(BaseSocket* session)
{
	SAFE_LOCK(lock_);
	auto iter = std::find(sessionList_.begin(), sessionList_.end(), session);

	if (iter != sessionList_.end())
	{
		cout << "[INFO] Find same session" << endl;
		return false;
	}
		
	if (sessionCount_ >= SESSION_CAPACITY)
	{
		cout << "[INFO] Full SessionList " << endl;
		return false;
	}
	
	session->SetId(CreateSessionId());
	sessionList_.push_back(session);

	return true;
}

bool SessionManager::CloseSession(BaseSocket * session)
{
	if (!session)
		return false;

	// TODO : Lock
	auto iter = std::find(sessionList_.begin(), sessionList_.end(), session);

	if (iter != sessionList_.end())
	{
		BaseSocket* closeSession = *iter;
		sessionList_.remove(closeSession);
		sessionCount_--;

		SAFE_DELETE(closeSession);
		return true;
	}
	
	return false;
}

BaseSocket * SessionManager::Session(int sessionId)
{
	for (auto session : sessionList_)
	{
		if (session->ID() == sessionId)
		{
			return session;
		}
	}

	cout << "[INFO] Not Found SessionID " << sessionId << endl;
	return nullptr;
}

int SessionManager::CreateSessionId()
{
	sessionCount_++;
	return sessionId_++;
}
