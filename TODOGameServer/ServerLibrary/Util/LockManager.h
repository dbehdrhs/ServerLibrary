#pragma once
class LockManager
{
public:
	LockManager();
	~LockManager();

	void lock()
	{
		std::recursive_mutex lock_;
		//std::lock(lock_, )
	}
};