#pragma once

#include<glm\glm.hpp>
#include"EventDispatcher.h"
#include<Windows.h>

struct InputEvent
{

	//enum EventType{ MBleft, MBmiddle, MBright, MouseMove, KeyEvent, CharacterKeyEvent };
	enum EventType{ MouseMove, MouseLButton, MouseRButton, MouseWheel, MouseMButton, KeyboardEvent, CharacterKeyEvent };
	enum KeyState{ KeyDown, KeyUp, nonKeyEvent };
	
	EventType type;
	KeyState state;
	int arg1;
	int arg2;
	
	InputEvent( EventType type, KeyState state, int arg1, int arg2 );

};

class Input : public EventDispatcher<InputEvent>
{

	public:
	
	Input();
	void trackMouse();
	bool handleWindowsMessages( UINT message, WPARAM parameter1, LPARAM parameter2 );
	
	private:
	
	glm::vec2 mouseDelta;
	glm::vec2 absoluteMousePosition;
	bool MouseKeyDown[3];
	HKL keyBoardLayout;
	
};