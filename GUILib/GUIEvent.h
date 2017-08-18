#pragma once
#include"Message.h"
#include<glm\glm.hpp>
namespace GUI
{
	enum GUIEventType{KeyEvent,LeftMouseButton,MiddleMouseButton,RightMouseButton};
	enum GUIEventState{KeyDown,KeyUp};

	struct GUIEvent
	{
		GUIEventType type;
		GUIEventState state;
		glm::vec2 position;
		bool processed;

		GUIEvent(
			GUIEventType type,
			GUIEventState state,
			const glm::vec2& position
		):processed(false)
		{
			this->type = type;
			this->state = state;
			this->position = position;
		}
	};
}