#include "W32Pump.h"

using namespace MessagePump;
W32Pump::W32Pump(const glm::vec2& resolution)
:resolution(resolution), isQuit(false)
{
	keyBoardLayout = GetKeyboardLayout(0);
}


void W32Pump::process()
{
	trackMouse();
	MSG msg;
	while(PeekMessage(&msg,0,0,0,PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		Message message;
		//keys
		if (msg.message == WM_CHAR)
		{
			message.type = MessageType::KeyPress;
			char key[2];
			if (GetKeyNameText(msg.lParam, key, 2) > 0)
			{
				message.state = MessageState::KeyDown;
				message.x = key[0];
				message.y = (TCHAR)msg.wParam;
			}
		}
		else if (msg.message == WM_KEYDOWN)
		{
			message.type = MessageType::KeyPress;
			message.state = MessageState::KeyDown;
			message.y = (TCHAR)msg.wParam;
		}
		else if (msg.message == WM_KEYUP)
		{
			message.type = MessageType::KeyPress;
			message.state = MessageState::KeyUp;
			message.y = (TCHAR)msg.wParam;
		}
		//mouse
		else if (msg.message == WM_KEYUP)
		{
			message.type = MessageType::KeyPress;
			message.state = MessageState::KeyUp;
			message.y = (TCHAR)msg.wParam;
		}
		else if (msg.message == WM_QUIT || msg.message == WM_DESTROY)
		{
			//message.type = MessageType::Exit;
			isQuit = true;
		}
		//TODO: process events other than key presses;
		this->sendMessage(message);
	}
}


bool W32Pump::quit()
{
	return isQuit;
}


void W32Pump::trackMouse()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouseDelta.x = absoluteMousePosition.x - cursorPos.x;
	mouseDelta.y = absoluteMousePosition.y - cursorPos.y;
	absoluteMousePosition.x = cursorPos.x;
	absoluteMousePosition.y = cursorPos.y;
	MouseMessage message;
	message.type = MessageType::MouseMove;
	message.state = MessageState::KeyDown;
	/*message.relativePosition.x = (float)cursorPos.x / resolution.x;
	message.relativePosition.y = (float)cursorPos.y / resolution.y;*/
	message.relativePosition.x = mouseDelta.x / resolution.x;
	message.relativePosition.y = mouseDelta.y / resolution.y;
	this->sendMessage(message);
}


LRESULT WINAPIV W32Pump::windowProcedure(
	HWND hndl_window,UINT message,WPARAM parameter1,LPARAM parameter2
)
{
    return DefWindowProc(hndl_window,message,parameter1,parameter2); 
}
