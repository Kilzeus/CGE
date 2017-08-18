#include"GUIContainer.h"

using namespace GUI;
GUIContainer::GUIContainer(const glm::vec2& topLeft,const glm::vec2& bottomRight)
{
}


bool GUIContainer::handleEvent(
	const GUI::GUIEvent& evt,class GUIElement& evtSource
)
{
	return false;
}


void GUIContainer::add(GUIContainable* widget)
{
	containables.push_back(widget);
}