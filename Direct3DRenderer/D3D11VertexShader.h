#pragma once
#include "vertexshader.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11VertexShader : public VertexShader
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11VertexShader* shader;
		D3D11VertexShader(VertexFormat* format,ID3D11VertexShader* shader);
	public:
	};
}
