#include "stdafx.h"
#include "LockManager.h"

const int INVALID_LINE = -1;

Lock::Lock(char* name)
{
	name_ = name;

	lockFile_.clear();
	lockLine_ = INVALID_LINE;

	lockId_ = LockManager::Instance().createLockId();
}

Lock::~Lock()
{
	name_.clear();
}

void Lock::lock(wstring fileName, int lineNo)
{
	mutex_.lock();

	lockFile_ = fileName;
	lockLine_ = lineNo;
}

void Lock::unlock()
{
	mutex_.unlock();

	lockFile_.clear();
	lockLine_ = INVALID_LINE;
}

////////////////////////////////////////////////////////////////////////////////
LockManager::LockManager()
{
	id_ = 0;
}

LockManager::~LockManager()
{
}

Lock * LockManager::searchLockCycle(Lock * newLock)
{
	Thread* thread = ThreadManager::Instance().At(GET_CURRENT_THREAD_ID);

	if (!thread)
		return nullptr;

	Lock* trace = newLock;
	Lock* deadLock = nullptr;

	while (true)
	{
		Lock* threadLock = thread->lock();
		if (threadLock->lockId() == trace->lockId())
		{
			// nuclear launched detected
			deadLock = threadLock;
			break;
		}
		thread = ThreadManager::Instance().At(threadLock->threadId());

		if (!thread)
			break;
	}

	return deadLock;
}

LockScope::LockScope(Lock * lock, wstring fileName, int lineNo)
{
	if (!lock)
		return;
	lock_ = lock;

	Lock* deadLock = LockManager::Instance().searchLockCycle(lock_);
	if (deadLock != nullptr)
	{
		// TODO : LOG
		return;
	}

	lock_->lock(fileName, lineNo);
	lock_->setThreadId(GET_CURRENT_THREAD_ID);
}

LockScope::~LockScope()
{
	if (!lock_)
		return;

	lock_->unlock();
	lock_->setThreadId(0);
}
