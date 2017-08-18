#include "Pump.h"

using namespace MessagePump;
Pump::Pump()
{
	for (int i = MessageType::Exit; i < MessageType::MouseMove+1; i++)
	{
		listeners.insert(std::make_pair((MessageType)i,new std::list<MessageListener*>));
	}
}


void Pump::sendMessage(const Message& message)
{
	std::map<MessageType,std::list<MessageListener*>*>::iterator iter =
		listeners.find(message.type);
	if(iter!=listeners.end())
	{
		std::list<MessageListener*>::iterator iListener = iter->second->begin();
		while(iListener!=iter->second->end())
		{
			(*iListener)->handle(message);
			iListener++;
		}
	}
}


void Pump::addListener(MessageType type, MessageListener* listener)
{
	std::map<MessageType, std::list<MessageListener*>*>::iterator iter =
		listeners.find(type);
	(iter->second)->push_back(listener);
}
