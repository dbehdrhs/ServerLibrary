#pragma once

#define MAKE_THREAD(className, func)  (new Thread(new thread_t(&className##::##func	, this), L#className))

class Thread
{
private:
	size_t id_;
	thread_t* thread_;
	//Lock* lock_;
	string name_;

public:
	Thread(thread_t* thread, string className);
	~Thread();

	void Init();
	void Release();

	size_t Id() { return id_; }
	string Name() { return name_; }
};

class ThreadManager : public Singleton<ThreadManager>
{
private:
	map<size_t, Thread*> threadPool_;
public:
	~ThreadManager();

	void Insert(Thread* thread);
	void Erase(size_t id);
	Thread* At(size_t id);
};