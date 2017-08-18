#pragma once
#include"GUIElement.h"
#include"GUIEvent.h"
#include"MessageListener.h"
#include"GUIRenderer.h"
#include<list>
namespace GUI
{
	/**
		Core interface for GUI system. Creates gui elements with
		skin.
	*/
	class GUICore : public MessagePump::MessageListener
	{
		GUIElement* root;
		GUIRenderer* renderer;
		GUISkin* skin;
	public:
		GUICore();
		bool handle(const MessagePump::Message& message);
		void setRoot(GUIElement* element);
		void setSkin(GUISkin* skin);
		GUIElement* createElement(
			const std::string id,
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight
		);
		class GUITextElement* createTextElement(
			const std::string id,
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight,
			const std::string text,
			float fontSize
		);
	};
}