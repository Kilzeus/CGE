#include"Input.h"
#include<windowsx.h>

Input::Input()
{

	this->keyBoardLayout = GetKeyboardLayout( 0 );

}

InputEvent::InputEvent( EventType type, KeyState state, int arg1, int arg2 )
{

	this->type = type;
	this->state = state;
	this->arg1 = arg1;
	this->arg2 = arg2;

}

bool Input::handleWindowsMessages( UINT message, WPARAM wParameter, LPARAM lParameter )
{

	switch( message )
	{
		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseMove, InputEvent::KeyDown, xPos, yPos ));
			return true;
		}
		case WM_LBUTTONDOWN: 
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseLButton, InputEvent::KeyDown, xPos, yPos ));
			return TRUE;
		}
		
		case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent ( InputEvent( InputEvent::MouseLButton, InputEvent::KeyUp, xPos, yPos ));
			return TRUE;
		}
		
		case WM_MBUTTONDOWN: 
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseMButton, InputEvent::KeyDown, xPos, yPos ));
			return TRUE;
		}
		case WM_MBUTTONUP:
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseMButton, InputEvent::KeyUp, xPos, yPos ));
			return TRUE;
		}
		
		case WM_RBUTTONDOWN: 
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseRButton, InputEvent::KeyDown, xPos, yPos ));
			return TRUE;
		}
		case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM( lParameter ); 
			int yPos = GET_Y_LPARAM( lParameter ); 
			this->dispatchEvent( InputEvent( InputEvent::MouseRButton, InputEvent::KeyUp, xPos, yPos ));
			return TRUE;
		}		
		case WM_CHAR: 
		{
			char key[2];
			if( GetKeyNameText( lParameter, key, 2 ) > 0 )
				this->dispatchEvent ( InputEvent( InputEvent::CharacterKeyEvent, InputEvent::KeyDown, (int)key[0], (TCHAR)wParameter ));
			return TRUE;
		}
		
		case WM_MOUSEWHEEL: 
		{
			int wheelMove = GET_WHEEL_DELTA_WPARAM( wParameter );
			this->dispatchEvent( InputEvent( InputEvent::MouseWheel, InputEvent::KeyDown, wheelMove, 0 ));
			return TRUE;
		}
		
		case WM_KEYUP: 
		{			
			//char key[2];
			//if(GetKeyNameText( lParameter, key, 2 ) > 0 )
			this->dispatchEvent( InputEvent( InputEvent::KeyboardEvent, InputEvent::KeyUp, 0, (TCHAR)wParameter ));
			return TRUE;
		}
		
		case WM_KEYDOWN: 
		{			
			//char key[2];
			//if(GetKeyNameText( lParameter, key, 2 ) > 0 )
			this->dispatchEvent( InputEvent( InputEvent::KeyboardEvent, InputEvent::KeyDown, 0, (TCHAR)wParameter ));
			return TRUE;
		}
	}
	return FALSE;
}


void Input::trackMouse()
{

	POINT cursorPos;
	GetCursorPos( &cursorPos );
	mouseDelta.x = absoluteMousePosition.x - cursorPos.x;	
	mouseDelta.y = absoluteMousePosition.y - cursorPos.y;
	absoluteMousePosition.x = cursorPos.x;
	absoluteMousePosition.y = cursorPos.y;	
	this->dispatchEvent( InputEvent( InputEvent::MouseMove, InputEvent::nonKeyEvent, cursorPos.x, cursorPos.y ));

}