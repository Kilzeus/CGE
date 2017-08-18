#include "GUITextElement.h"

using namespace GUI;
GUITextElement::GUITextElement(
	const std::string id,
	const glm::vec2& topLeft,
	const glm::vec2& bottomRight,
	const std::string text,
	float fontSize
	) :GUIElement(id, topLeft, bottomRight), 
	text(text), fontSize(fontSize), isSizeRelative(true)
{
}


GUITextElement::~GUITextElement()
{
}


void GUITextElement::setText(const std::string text)
{
	this->text = text;
}


void GUITextElement::setTextWrapping(bool enable)
{
	wrap = enable;
}
