#pragma once
#include "vertexbuffer.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11VertexBuffer : public VertexBuffer
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11Buffer* buffer;
		ID3D11DeviceContext* renderContext;
		D3D11VertexBuffer(
			ID3D11Buffer* buffer,
			ID3D11DeviceContext* renderContext,
			bool dynamic
		);
	public:
		~D3D11VertexBuffer();
		void setData(Resource* data);
		void setData(
			Resource* data,UINT numVertices,UINT vertexByteSize
		);
	};
}
