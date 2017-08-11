#ifndef EVENTDISPATCHER_HH
#define EVENTDISPATCHER_HH

#include<list>
#include<string>

template<typename T>
class EventReceiver
{

	public:
	
	virtual bool processMessage( T& event )=0;
	
};

template<typename T>
class EventDispatcher
{

	public:
	
	void registerReceiver( EventReceiver<T>* receiver )
	{
		this->receivers.push_back( receiver );
	}
	
	void dispatchEvent( T& event )
	{
		std::list<EventReceiver<T>*>::iterator iter = this->receivers.begin();
		while( iter != this->receivers.end())
		{
			if((*iter)->processMessage( event )) return;
			else iter++;
		}
	}
	
	void unregisterReceiver( EventReceiver<T>* receiver )
	{
		this->receivers.remove( receiver );
	}
	
	private:
	
	std::list<EventReceiver<T>*> receivers;

};

#endif