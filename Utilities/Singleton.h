#pragma once

template<typename T>
class Singleton
{
	
	public:
	
	static T& getSingleton()
	{
		if(!Singleton<T>::instance ) Singleton<T>::instance = new T;
		return *Singleton<T>::instance;
	}

	protected:
	
	Singleton() {};
	static T* instance;

};

template<typename T>
T* Singleton<T>::instance = 0;