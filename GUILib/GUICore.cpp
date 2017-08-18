#include"GUICore.h"
#include"GUITextElement.h"

using namespace GUI;
GUICore::GUICore()
	:root(0)
{
}

/**
	Hot swaps the UI skin and applies the new skin to all elements.
*/
void GUICore::setSkin(GUISkin* skin)
{
	this->skin = skin;
	if(root) root->setSkinRecursive(skin);
}


bool GUICore::handle(const MessagePump::Message& message)
{
	if(root)
	{
		GUIEventType type;
		GUIEventState state;
		glm::vec2 position;
		if(message.type == MessagePump::LeftMouseButton) type = LeftMouseButton;
		if(message.type == MessagePump::MiddleMouseButton) type = MiddleMouseButton;
		if(message.type == MessagePump::RightMouseButton) type = RightMouseButton;
		if(message.type == MessagePump::KeyPress) type = KeyEvent;
		if(message.state == MessagePump::KeyDown) state = KeyDown;
		if(message.state == MessagePump::KeyUp) state = KeyUp;
		GUIEvent evt(type,state,position);
		root->handleEvent(evt);
		return evt.processed;
	}
	else return false;
}


GUITextElement* GUICore::createTextElement(
	const std::string id,
	const glm::vec2& topLeft,
	const glm::vec2& bottomRight,
	const std::string text,
	float fontSize)
{
	GUITextElement* element = new GUITextElement(id, topLeft, bottomRight, text, fontSize);
	element->renderable = skin->get(id);
	element->wrap = true;
	return element;
}


GUIElement* GUICore::createElement(
	const std::string id,
	const glm::vec2& topLeft,
	const glm::vec2& bottomRight
)
{
	GUIElement* element = new GUIElement(id,topLeft,bottomRight);
	element->renderable = skin->get(id);
	return element;
}