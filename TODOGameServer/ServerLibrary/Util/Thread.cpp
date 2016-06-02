#include "stdafx.h"
#include "Thread.h"


Thread::Thread(thread_t * thread, string className)
	:thread_(thread), name_(className)
{
	id_ = std::hash<thread_t::id>()(thread->get_id());
	
	Init();
}

Thread::~Thread()
{
	Release();
}

void Thread::Init()
{
	ThreadManager::Instance().Insert(this);
}

void Thread::Release()
{
	thread_->join();

	SAFE_DELETE(thread_);
}

//----------------------------------------------------
ThreadManager::~ThreadManager()
{
	for (auto iter : threadPool_)
	{
		SAFE_DELETE(iter.second);
	}

	cout << "[INFO] ThreadManager Release" << endl;
}

void ThreadManager::Insert(Thread * thread)
{
	std::pair<size_t, Thread*> node(thread->Id(), thread);
	threadPool_.insert(node);

	cout << "Create Thread id : " << thread->Id() << " name : " << thread->Name().c_str() << endl;
}

void ThreadManager::Erase(size_t id)
{
	auto iter = threadPool_.find(id);
	if (iter == threadPool_.end())
	{
		cout << "Not find thread id" << endl;
		return;
	}

	threadPool_.erase(iter);
	SAFE_DELETE(iter->second);

	cout << "thread pop" << endl;
}

Thread * ThreadManager::At(size_t id)
{
	auto data = threadPool_.find(id);

	if (data == threadPool_.end())
		return nullptr;

	return data->second;
}