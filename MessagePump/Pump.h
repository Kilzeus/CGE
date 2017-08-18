#pragma once
#include"MessageListener.h"
#include<map>
#include<list>
namespace MessagePump
{
	class Pump
	{
		std::map<MessageType,std::list<MessageListener*>*> listeners;
	protected:
		void sendMessage(const Message& message);
	public:
		Pump();
		virtual void process()=0;
		void addListener(MessageType type, MessageListener* listener);
		virtual bool quit() = 0; //easy way to check if quit-msg has been received.
	};
}
