#pragma once

#define SAFE_LOCK(lock) LockScope __lockSafe(&lock, _W(__FILE__), __LINE__);

class Lock
{
private:
	lock_t mutex_;
	string name_;
	size_t lockId_;
	size_t threadId_;

	wstring lockFile_;
	int lockLine_;
public:
	Lock(char* name);
	virtual ~Lock();

	void lock(wstring fileName, int lineNo);
	void unlock();

	const char* name() { return name_.data(); }
	size_t lockId() { return lockId_; }
	size_t threadId() { return threadId_; }
	lock_t& mutex() { return mutex_; }
	
	void setThreadId(size_t id) { threadId_ = id; }
};

////////////////////////////////////////////////////////
class LockScope
{
private:
	Lock* lock_;

public:
	LockScope(Lock* lock, wstring fileName, int lineNo);
	~LockScope();
};

////////////////////////////////////////////////////////
class LockManager : public Singleton<LockManager>
{
public:
	LockManager();
	~LockManager();

	size_t createLockId() { return id_++; }

	Lock* searchLockCycle(Lock* newLock);

private:
	size_t id_;
};