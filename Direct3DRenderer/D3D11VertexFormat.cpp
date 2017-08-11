#include "D3D11VertexFormat.h"

using namespace Renderer;
D3D11VertexFormat::D3D11VertexFormat(ID3D11Device* device)
:device(device)
{
	device->AddRef();
}


D3D11VertexFormat::~D3D11VertexFormat()
{
	device->Release();
}


void D3D11VertexFormat::finish(Resource* vertexShader)
{
	D3D11_INPUT_ELEMENT_DESC* desc
		 = new D3D11_INPUT_ELEMENT_DESC[elements.size()];
	for(int i=0;i<elements.size();i++)
	{
		DXGI_FORMAT format;
		switch(elements[i].getType())
		{
			case FLOAT1:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
						break;
			}
			case FLOAT2:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
						break;
			}
			case FLOAT3:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
						break;
			}
			case FLOAT4:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
			}
			case Int1:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
						break;
			}
			case Int2:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
						break;
			}
			case Int3:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
						break;
			}
			case Int4:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
						break;
			}
			case UInt1:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
						break;
			}
			case UInt2:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
						break;
			}
			case UInt3:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
						break;
			}
			case UInt4:{
						format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
						break;
			}
		}
		desc[i].SemanticName = elements[i].getSemantic().c_str();
		desc[i].SemanticIndex = elements[i].getIndex();
		desc[i].InputSlot = 0;
		desc[i].Format = format;
		desc[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		desc[i].InstanceDataStepRate = 0;
		if(!elements[i].isInstanceData()) desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		else desc[i].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	}
	HRESULT result = device->CreateInputLayout(
		desc,elements.size(),vertexShader->getData(),vertexShader->getSize(),&inputLayout
	);
	delete[] desc;
}