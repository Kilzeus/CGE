#pragma once
#include"Definitions.h"
namespace Renderer
{
	struct Uint2
	{
		UINT x,y;

		Uint2() :x(0),y(0) {};
		Uint2(UINT x, UINT y) :x(x), y(y) {};
	};
	struct Float2
	{
		float x,y;

		Float2() :x(0.f), y(0.f) {};
		Float2(float x, float y) :x(x), y(y) {};
	};
	enum FormatType{ R32_Float, R32G32_Float, R32G32B32_Float, 
	R32G32B32A32_Float, R32_Uint, R32G32_Uint, R32G32B32_Uint, 
	R32G32B32A32_Uint, R16_Float, R16G16_Float, R16G16B16_Float, 
	R16G16B16A16_Float, R8G8B8A8_Unorm };
}