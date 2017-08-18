#pragma once
#include"Definitions.h"
#include<glm\glm.hpp>
namespace MessagePump
{
	enum MessageType{
		Exit,Resize,KeyPress,LeftMouseButton,MiddleMouseButton,RightMouseButton, MouseMove
	};
	enum MessageState{
		KeyDown,KeyUp	// apply to mousebuttons and keys
	};
	struct Message
	{
		MessageType type;
		MessageState state;
		UINT x;
		UINT y;
	};

	struct MouseMessage : public Message
	{
		glm::vec2 relativePosition;
	};
}
