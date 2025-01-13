#pragma once

template<class Class>
class Singleton
{
public:
	static Class* Get()
	{
		if (instance == nullptr)
			instance = new Class();
		return instance;
	}

	static void Delete()
	{
		delete instance;
	}

private:
	static Class* instance;
};

template<class Class>
Class* Singleton<Class>::instance = nullptr;