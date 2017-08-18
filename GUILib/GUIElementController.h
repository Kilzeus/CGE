#pragma once
#include"GUIEvent.h"
namespace GUI
{
	class GUIElementController
	{
	public:
		virtual bool handleEvent(const GUIEvent& evt,class GUIElement& evtSource)=0;
	};
}