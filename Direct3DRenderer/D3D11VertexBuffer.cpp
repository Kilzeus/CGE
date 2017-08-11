#include "D3D11VertexBuffer.h"

using namespace Renderer;
D3D11VertexBuffer::D3D11VertexBuffer(
	ID3D11Buffer* buffer,
	ID3D11DeviceContext* renderContext,
	bool dynamic
	) :buffer(buffer), renderContext(renderContext)
{
	renderContext->AddRef();
	this->dynamic = dynamic;
}


D3D11VertexBuffer::~D3D11VertexBuffer()
{
	renderContext->Release();
}


void D3D11VertexBuffer::setData(
	Resource* data,UINT numVertices,UINT vertexByteSize
)
{
	this->numVertices = numVertices;
	this->vertexByteSize = vertexByteSize;
	this->size = data->getSize();
	if (!dynamic)
	{
		renderContext->UpdateSubresource(
			buffer, 0, 0, data->getData(), 0, 0
		);
	}
	else
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		renderContext->Map(buffer, 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &mappedResource);
		memcpy(&mappedResource.pData, data->getData(),data->getSize());
		renderContext->Unmap(buffer, 0);
	}
}


void D3D11VertexBuffer::setData(Resource* data)
{
	UINT byteSize = 0;
	this->size = data->getSize();
	renderContext->UpdateSubresource(
		buffer,0,0,data->getData(),0,0
	);
}