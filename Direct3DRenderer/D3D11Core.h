#pragma once
#include"Core.h"
#include"D3D11Device.h"
#include"Pump.h"
namespace Renderer
{
	class D3D11Core : public Core
	{
		D3D11Device* device;
	public:
		D3D11Core();
		~D3D11Core();
		RenderWindow* createRenderWindow(Uint2 resolution,MessagePump::Pump* pump);
		Device* createDevice(RenderWindow* renderWindow,const DeviceProperties& properties);
	};
}