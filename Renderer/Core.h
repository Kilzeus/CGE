#pragma once
#include"RenderContext.h"
#include"Device.h"
#include"RenderWindow.h"
#include"Pump.h"
namespace Renderer
{

	/**
		Core represents the entire rendering subsystem. You select
		which rendering system to use by instantiating one of the
		implementations of the Core-interface.
	*/
	class Core
	{
	public:
		virtual RenderWindow* createRenderWindow(Uint2 resolution,MessagePump::Pump* pump)=0;
		virtual Device* createDevice(RenderWindow* renderWindow,const DeviceProperties& properties)=0;
	};
}
