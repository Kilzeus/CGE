#include"D3D11Device.h"
#include"D3D11VertexShader.h"
#include"D3D11IndexBuffer.h"
#include"D3D11VertexBuffer.h"
#include"D3D11Texture.h"
#include"D3D11FragmentShader.h"
#include"D3D11GeometryShader.h"
#include"D3D11RenderTargetView.h"
#include"D3D11GPUBuffer.h"
#include"D3D11RenderContext.h"
#include"D3D11VertexFormat.h"
#include<D3Dcompiler.h>
#include<iostream>

using namespace Renderer;
D3D11Device::D3D11Device(
	const DeviceProperties& properties,
	ID3D11Device* device,
	ID3D11DeviceContext* renderContext,
	IDXGISwapChain* swapChain,
	D3D_FEATURE_LEVEL featureLevel,
	ID3D11DepthStencilView* depthStencil,
	ID3D11RenderTargetView* backBufferView
)
:Device(properties), device(device), iRenderContext(renderContext),
swapChain(swapChain),featureLevel(featureLevel),
renderContext(0),depthStencil(depthStencil),
backBuffer(new D3D11RenderTargetView(backBufferView)),
screenSpaceTopLeft(-1,1)
{
}


RenderTargetView* D3D11Device::getBackBuffer()
{
	return backBuffer;
}


VertexShader* D3D11Device::createVertexShader(
	Resource* resource,VertexFormat* format
)
{
	format->finish(resource);
	ID3D11VertexShader* iShader = 0;
	HRESULT result = device->CreateVertexShader(
		(void*)resource->getData(),resource->getSize(),0,&iShader
	);
	D3D11VertexShader* shader = new D3D11VertexShader(format,iShader);
	return shader;
}

FragmentShader* D3D11Device::createFragmentShader(
	Resource* resource
)
{
	ID3D11PixelShader* iShader = 0;
	HRESULT result = device->CreatePixelShader(
		(void*)resource->getData(),resource->getSize(),0,&iShader
	);
	FragmentShader* shader = new D3D11FragmentShader(iShader);
	return shader;
}


GeometryShader* D3D11Device::createGeometryShader(Resource* resource)
{
	ID3D11GeometryShader* iShader = 0;
	HRESULT result = device->CreateGeometryShader(
		(void*)resource->getData(),resource->getSize(),0,&iShader
	);
	GeometryShader* shader = new D3D11GeometryShader(iShader);
	return shader;
}


TessellationControlShader* D3D11Device::createTessellationConrolShader(Resource* resource)
{
	ID3D11HullShader* ishader = 0;
	HRESULT result = device->CreateHullShader((void*)resource->getData(), resource->getSize(), 0, &ishader);
	return 0;
}


TessellationEvaluationShader* D3D11Device::createTessellationEvaluationShader(Resource* resource)
{
	return 0;
}


void D3D11Device::createDefaultSampler()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MaxAnisotropy = 16;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = device->CreateSamplerState(&desc, &defaultSamplerState);
	if (hr)
	{
		std::cout << "error when creating default sampler state";
	}
}


IndexBuffer* D3D11Device::createIndexBuffer(UINT byteSize,IndexDataFormat format)
{
	ID3D11Buffer* buffer = 0;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = byteSize;

	device->CreateBuffer(&desc,0,&buffer);
	IndexBuffer* indexBuffer = new D3D11IndexBuffer(format,buffer,iRenderContext);
	return indexBuffer;
}


VertexBuffer* D3D11Device::crateVertexBuffer(UINT byteSize,bool dynamic)
{
	ID3D11Buffer* buffer = 0;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	if(dynamic)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = byteSize;

	HRESULT hr = device->CreateBuffer(&desc,0,&buffer);
	VertexBuffer* vertexBuffer = new D3D11VertexBuffer(buffer,iRenderContext,dynamic);
	return vertexBuffer;
}


Texture* D3D11Device::createTexture(
	Resource* resource,Uint2 dimensions,
	TextureFormat format, UINT arraySize, 
	bool writeAcces, bool renderTarget
)
{
	ID3D11Texture2D* iTexture = 0;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_TEXTURE2D_DESC));
	
	desc.Width = dimensions.x;
	desc.Height = dimensions.y;
	UINT mips = 1;
	if(format==TextureFormat::R16G16B16A16_float) desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	else if (format == TextureFormat::R32G32_float) desc.Format = DXGI_FORMAT_R32G32_FLOAT;
	else if (format == TextureFormat::R16G16_float) desc.Format = DXGI_FORMAT_R16G16_FLOAT;
	else if (format == TextureFormat::R8G8B8A8_unorm) desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (format == TextureFormat::R8G8B8A8_sint) desc.Format = DXGI_FORMAT_R8G8B8A8_SINT;
	else if (format == TextureFormat::R8G8B8A8_uint) desc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
	else if (format == TextureFormat::B8G8R8A8_unorm) desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	else if (format == TextureFormat::R32_float) desc.Format = DXGI_FORMAT_R32_FLOAT;
	else if (format == TextureFormat::R8_sint) desc.Format = DXGI_FORMAT_R8_SINT;
	else if (format == TextureFormat::R8_uint) desc.Format = DXGI_FORMAT_R8_UINT;
	else if (format == TextureFormat::R8_unorm) desc.Format = DXGI_FORMAT_R8_UNORM;
	else if (format == TextureFormat::R16G16B16A16_unorm) desc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
	if (renderTarget)
	{
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
		mips = 0;
	}
	else
	{
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	}
	if (writeAcces)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else desc.Usage = D3D11_USAGE_DEFAULT;
	desc.MipLevels = mips;
	desc.SampleDesc.Count = 1;
	desc.ArraySize = arraySize;

	HRESULT result = 0;
	if(resource)
	{
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = resource->getData();
		data.SysMemPitch = resource->getPitch();
		result = device->CreateTexture2D(&desc,&data,&iTexture);
		if (result)
			return 0;
	}
	else result = device->CreateTexture2D(&desc,0,&iTexture);
	ID3D11ShaderResourceView* view = 0;
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	viewDesc.Format = desc.Format;
	if(arraySize > 1)
	{
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		viewDesc.Texture2DArray.ArraySize = arraySize;
		viewDesc.Texture2DArray.MipLevels = -1;
	}
	else
	{
		viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		viewDesc.Texture2D.MipLevels = -1;
	}
	result = device->CreateShaderResourceView(iTexture,&viewDesc,&view);

	D3D11Texture* texture = new D3D11Texture(
		renderTarget, format, iTexture, view, dimensions, arraySize
	);
	texture->usage = desc.Usage;
	return texture;
}


RenderTargetView* D3D11Device::createRenderTarget(Texture* resource)
{
	ID3D11RenderTargetView* iView = 0;
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
	D3D11Texture* texture = (D3D11Texture*)resource;

	if (texture->getFormat() == TextureFormat::R16G16B16A16_float) desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	else if (texture->getFormat() == TextureFormat::R32G32_float) desc.Format = DXGI_FORMAT_R32G32_FLOAT;
	else if (texture->getFormat() == TextureFormat::R16G16_float) desc.Format = DXGI_FORMAT_R16G16_FLOAT;
	else if (texture->getFormat() == TextureFormat::R8G8B8A8_unorm) desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	else if (texture->getFormat() == TextureFormat::R8G8B8A8_sint) desc.Format = DXGI_FORMAT_R8G8B8A8_SINT;
	else if (texture->getFormat() == TextureFormat::R8G8B8A8_uint) desc.Format = DXGI_FORMAT_R8G8B8A8_UINT;
	else if (texture->getFormat() == TextureFormat::B8G8R8A8_unorm) desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	else if (texture->getFormat() == TextureFormat::R32_float) desc.Format = DXGI_FORMAT_R32_FLOAT;
	else if (texture->getFormat() == TextureFormat::R8_sint) desc.Format = DXGI_FORMAT_R8_SINT;
	else if (texture->getFormat() == TextureFormat::R8_uint) desc.Format = DXGI_FORMAT_R8_UINT;
	else if (texture->getFormat() == TextureFormat::R8_unorm) desc.Format = DXGI_FORMAT_R8_UNORM;
	else if (texture->getFormat() == TextureFormat::R16G16B16A16_unorm) desc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;

	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	HRESULT result = device->CreateRenderTargetView(texture->texture,&desc,&iView);
	D3D11RenderTargetView* view = new D3D11RenderTargetView(iView);
	return view;
}


RenderContext* D3D11Device::getRenderContext()
{
	if (!renderContext)
	{
		D3D11RenderContext* rc = new D3D11RenderContext(
			device, iRenderContext, depthStencil, swapChain);

		// Setup the viewport for rendering.
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		rc->viewport.Width = (float)resolution.x;
		rc->viewport.Height = (float)resolution.y;
		rc->viewport.MinDepth = 0.0f;
		rc->viewport.MaxDepth = 1.0f;
		rc->viewport.TopLeftX = 0.0f;
		rc->viewport.TopLeftY = 0.0f;
		

		rc->backBuffer = backBuffer;
		renderContext = rc;
		rc->setViewports(1);
	}
	return renderContext;
}


GPUBuffer* D3D11Device::createGPUBuffer(UINT byteSize)
{
	ID3D11Buffer* buffer = 0;
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));

	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = byteSize;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	//desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = device->CreateBuffer(&desc,0,&buffer);
	GPUBuffer* gpubuffer = new D3D11GPUBuffer(buffer,iRenderContext);
	return gpubuffer;
}


Resource* D3D11Device::compileShaderFromFile(
	const std::wstring& filename,std::string shaderProfile
)
{
	ID3D10Blob* shaderBlob = 0;
	ID3D10Blob* errors = 0;
	HRESULT result = D3DCompileFromFile(
		filename.c_str(),0,0,"main",shaderProfile.c_str()
		,0,0,&shaderBlob,&errors
	);
	if (result)
	{
		std::string error((char*)errors->GetBufferPointer());
		std::cerr << error;
 		std::cout << error;
	}
	//std::string error = (char*)errors->GetBufferPointer();
	Resource* shader = new Resource(
		shaderBlob->GetBufferSize(),shaderBlob->GetBufferPointer()
	);
	return shader;
}


VertexFormat* D3D11Device::createVertexFormat()
{
	return new D3D11VertexFormat(device);
}


const Float2& D3D11Device::getScreenSpaceTopLeft()
{
	return screenSpaceTopLeft;
}


const Uint2& D3D11Device::getResolution()
{
	return resolution;
}