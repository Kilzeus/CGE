#pragma once
#include"GUIContainer.h"
namespace GUI
{
	class GUIWindow : public GUIContainer
	{
	protected:
		bool hasTitlebar;
	public:
		GUIWindow(const glm::vec2& topLeft,const glm::vec2& bottomRight);
	};
}