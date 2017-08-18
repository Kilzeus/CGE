#pragma once
#include"Message.h"
namespace MessagePump
{
	class MessageListener
	{
	public:
		virtual bool handle(const Message& message)=0;
	};
}
