#pragma once
#include"Pump.h"
#include<Windows.h>
namespace MessagePump
{
	class W32Pump : public Pump
	{
		glm::vec2 mouseDelta;
		glm::vec2 absoluteMousePosition;
		bool MouseKeyDown[3];
		HKL keyBoardLayout;
		glm::vec2 resolution;
		bool isQuit;

		void trackMouse();
	public:
		W32Pump(const glm::vec2& resolution);
		void process();
		bool quit();
		static LRESULT WINAPIV windowProcedure( 
			HWND hndl_window,UINT message,WPARAM parameter1,LPARAM parameter2 
		);
	};
}
