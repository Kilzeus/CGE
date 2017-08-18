#include"GUIWindow.h"

using namespace GUI;
GUIWindow::GUIWindow(const glm::vec2& topLeft,const glm::vec2& bottomRight)
	:GUIContainer(topLeft,bottomRight)
{
	//root = new GUI::GUIElement(std::string("background"),topLeft,bottomRight);
}