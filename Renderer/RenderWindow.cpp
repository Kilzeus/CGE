#include "RenderWindow.h"

using namespace Renderer;
RenderWindow::RenderWindow()
{
}


RenderWindow::RenderWindow(const Uint2& position,const Uint2& dimensions)
:position(position),dimensions(dimensions)
{
	this->dimensions = dimensions;
}


void RenderWindow::setDimenstions(const Uint2& dimensions)
{
	this->dimensions = dimensions;
}


bool RenderWindow::isFullScreen() const
{
	return fullScreen;
}


const Uint2& RenderWindow::getDimensions()
{
	return dimensions;
}
