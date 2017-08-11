#pragma once
#include "gpubuffer.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11GPUBuffer : public GPUBuffer
	{
		friend class D3D11Device;
		friend class D3D11RenderContext;
	protected:
		ID3D11Buffer* buffer;
		ID3D11DeviceContext* renderContext;
		D3D11GPUBuffer(
			ID3D11Buffer* buffer,
			ID3D11DeviceContext* renderContext
		);
		~D3D11GPUBuffer();
	public:
		void setData(Resource* data);
	};
}
