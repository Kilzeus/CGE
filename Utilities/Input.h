#ifndef INPUT_HHH
#define INPUT_HHH

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

class Input : public EventDispatcher<InputEvent>, public Singleton<Input>
{

	public:
	
	Input();
	void trackMouse();
	bool handleWindowsMessages( UINT message, WPARAM parameter1, LPARAM parameter2 );
	
	private:
	
	XMFLOAT2 mouseDelta;
	XMFLOAT2 absoluteMousePosition;
	bool MouseKeyDown[3];
	HKL keyBoardLayout;
	
};


#endif