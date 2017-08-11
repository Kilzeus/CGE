#pragma once
#include "vertexformat.h"
#include"Resource.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11VertexFormat : public VertexFormat
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11InputLayout* inputLayout;
		ID3D11Device* device;
		D3D11VertexFormat(ID3D11Device* device);
	public:
		~D3D11VertexFormat();
		void finish(Resource* vertexShader);
	};
}
