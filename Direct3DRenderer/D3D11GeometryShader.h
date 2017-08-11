#pragma once
#include"GeometryShader.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11GeometryShader : public GeometryShader
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11GeometryShader* shader;
		D3D11GeometryShader(ID3D11GeometryShader* shader);
	public:
	};
}
