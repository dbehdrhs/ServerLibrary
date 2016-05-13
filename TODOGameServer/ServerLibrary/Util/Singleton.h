#pragma once

template<class T>
class Singleton
{
protected:
	Singleton()	{}
	~Singleton() {}

public:
	Singleton(const Singleton&);
	Singleton& operation = (const Singleton&);

	static T& Instance()
	{
		static T instance;
		return instance;
	}
};
