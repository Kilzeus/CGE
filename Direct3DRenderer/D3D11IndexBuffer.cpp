#include "D3D11IndexBuffer.h"

using namespace Renderer;
D3D11IndexBuffer::D3D11IndexBuffer(
	IndexDataFormat format,
	ID3D11Buffer* buffer,
	ID3D11DeviceContext* renderContext
):IndexBuffer(format),buffer(buffer),
renderContext(renderContext)
{
	renderContext->AddRef();
	if(format==IndexDataFormat::Int16)
		d3dFormat = DXGI_FORMAT_R16_UINT;
	else
		d3dFormat = DXGI_FORMAT_R32_UINT;
}


D3D11IndexBuffer::~D3D11IndexBuffer()
{
	renderContext->Release();
}


void D3D11IndexBuffer::setData(Resource* data)
{
	renderContext->UpdateSubresource(
		buffer,0,0,data->getData(),0,0
	);
}


void D3D11IndexBuffer::setData(Resource* data,UINT numIndices)
{
	this->numIndices = numIndices;
	renderContext->UpdateSubresource(
		buffer,0,0,data->getData(),0,0
	);
}