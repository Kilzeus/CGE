#include "D3D11GPUBuffer.h"

using namespace Renderer;
D3D11GPUBuffer::D3D11GPUBuffer(
	ID3D11Buffer* buffer,
	ID3D11DeviceContext* renderContext
):buffer(buffer),renderContext(renderContext)
{
	renderContext->AddRef();
}


D3D11GPUBuffer::~D3D11GPUBuffer()
{
	renderContext->Release();
}


void D3D11GPUBuffer::setData(Resource* data)
{
	/*renderContext->UpdateSubresource(
		buffer, 0, 0, data->getData(), 0,0
	);*/
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT hr = renderContext->Map(buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, data->getData(), data->getSize());
	renderContext->Unmap(buffer, 0);
}
