#include "W32RenderWindow.h"

using namespace Renderer;
W32RenderWindow::W32RenderWindow(HWND windowHandle)
:windowHandle(windowHandle)
{
}


HWND W32RenderWindow::getWindowHandle() const
{
	return windowHandle;
}


void W32RenderWindow::open()
{
	ShowWindow(windowHandle,1);
}


void W32RenderWindow::close()
{
	ShowWindow(windowHandle,1);
}