#pragma once
#include "indexbuffer.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11IndexBuffer : public IndexBuffer
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
		ID3D11Buffer* buffer;
		ID3D11DeviceContext* renderContext;
		DXGI_FORMAT d3dFormat;
		D3D11IndexBuffer(
			IndexDataFormat format,
			ID3D11Buffer* buffer,
			ID3D11DeviceContext* renderContext
		);
	public:
		~D3D11IndexBuffer();
		void setData(Resource* data);
		void setData(Resource* data,UINT numIndices);
	};
}
