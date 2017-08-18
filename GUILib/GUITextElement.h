#pragma once
#include"GUIElement.h"
namespace GUI
{
	class GUITextElement : public GUIElement
	{
		friend class FontRenderer;
		friend class GUICore;
	protected:
		std::string text;
		bool wrap;
		float fontSize;
		bool isSizeRelative;

		GUITextElement(
			const std::string id,
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight,
			const std::string text,
			float fontSize);
	public:
		~GUITextElement();
		void setText(const std::string text);
		void setTextWrapping(bool enable);
	};
}

