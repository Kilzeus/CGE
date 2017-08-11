#pragma once
#include "renderwindow.h"
#include<Windows.h>
namespace Renderer
{
	class W32RenderWindow : public RenderWindow
	{
		friend class D3D11Core;
		HWND windowHandle;
		W32RenderWindow(HWND windowHandle);
	public:
		HWND getWindowHandle() const;
		void open();
		void close();
	};
}
