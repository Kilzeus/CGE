#pragma once
#include"GUIContainable.h"
namespace GUI
{
	/**
		base container for holding other types of widgets.
	*/
	class GUIContainer : public GUI::GUIElementController
	{
	protected:
		GUI::GUIElement* root;
		std::list<GUIContainable*> containables;
	public:
		GUIContainer(const glm::vec2& topLeft,const glm::vec2& bottomRight);
		bool handleEvent(const GUI::GUIEvent& evt,class GUIElement& evtSource);
		void add(GUIContainable* widget);
	};
}