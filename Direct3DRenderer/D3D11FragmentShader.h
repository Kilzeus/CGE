#pragma once
#include "fragmentshader.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11FragmentShader : public FragmentShader
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11PixelShader* shader;
		D3D11FragmentShader(ID3D11PixelShader* shader);
	public:
	};
}
