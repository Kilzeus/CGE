#include"Direct3DRenderer.h"
#include<sstream>
#include<Xnamath.h>

DrawTarget::DrawTarget()
{

	const UINT numVertices = 4;
	UINT index = 0;
	DrawTargetVertex* vertices = new DrawTargetVertex[numVertices];
	
	vertices[index].x = -1.0f;
	vertices[index].y = 1.0f;
	vertices[index].u = 0.0f;
	vertices[index].v = 0.0f;
	index++;
	vertices[index].x = 1.0f;
	vertices[index].y = 1.0f;
	vertices[index].u = 1.0f;
	vertices[index].v = 0.0f;
	index++;
	vertices[index].x = -1.0f;
	vertices[index].y = -1.0f;
	vertices[index].u = 0.0f;
	vertices[index].v = 1.0f;
	index++;
	vertices[index].x = 1.0f;
	vertices[index].y = -1.0f;
	vertices[index].u = 1.0f;
	vertices[index].v = 1.0f;
	index++;
	
	D3D11_BUFFER_DESC desc;
	ZeroMemory( &desc, sizeof( D3D11_BUFFER_DESC ));

	desc.ByteWidth = sizeof(DrawTargetVertex)*numVertices;
	desc.Usage = D3D11_USAGE_DEFAULT; 
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory( &data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices;

	if(FAILED( DeferredRenderer::getSingleton().getDevice()->CreateBuffer( &desc, &data, &this->vertexbuffer )))
		Logger::getSingleton().logEntry( "ERROR","Vertexbuffer problem" );
		
	const UINT numIndices = 6;
	UINT *indices = new UINT[numIndices];
	for( int i = 0; i < numIndices; i++ )
	{
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 3;
		indices[5] = 2;
	}
	D3D11_BUFFER_DESC descIndex;
	ZeroMemory(&descIndex, sizeof(D3D11_BUFFER_DESC));

	descIndex.ByteWidth = sizeof(UINT)*numIndices;
	descIndex.Usage = D3D11_USAGE_DEFAULT; 
	descIndex.BindFlags = D3D11_BIND_INDEX_BUFFER;
	descIndex.CPUAccessFlags = 0; //D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	descIndex.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data2;
	ZeroMemory( &data2, sizeof(D3D11_SUBRESOURCE_DATA));

	data2.pSysMem = indices;
	data2.SysMemPitch = 0;
	data2.SysMemSlicePitch = 0;

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreateBuffer( &descIndex, &data2, &this->indexbuffer )))
		Logger::getSingleton().logEntry( "ERROR","Indexbuffer problem" );
	
	this->composeLayout();

}

void DrawTarget::composeLayout()
{

	const UINT numDecsriptions = 2;
	D3D11_INPUT_ELEMENT_DESC inputDesc[numDecsriptions];
	ZeroMemory( inputDesc, sizeof(D3D11_INPUT_ELEMENT_DESC)*numDecsriptions);
	
	inputDesc[0].SemanticName = "SV_POSITION";
	inputDesc[0].SemanticIndex = 0;
	inputDesc[0].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputDesc[0].AlignedByteOffset = 0;
	inputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	inputDesc[1].SemanticName = "TEXCOORDS";
	inputDesc[1].SemanticIndex = 0;
	inputDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	inputDesc[1].AlignedByteOffset = 2*sizeof(float);
	inputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

	if(FAILED(DeferredRenderer::getSingleton().getDevice()->CreateInputLayout( inputDesc, numDecsriptions, ShaderManager::getSingleton().getVertexShader( "composer.vsh" )->shaderBlob->GetBufferPointer(), ShaderManager::getSingleton().getVertexShader( "composer.vsh" )->shaderBlob->GetBufferSize(), &this->inputLayout )))
		MessageBox ( 0, "Failed to create inputlayout", "ERROR", MB_OK );

}

void DrawTarget::setResources( ID3D11DeviceContext* devContext, PShader* pshader, VShader* vshader )
{

	UINT offset = 0;
	UINT stride = sizeof(DrawTargetVertex);
	devContext->VSSetShader( vshader->vertexShader, 0, 0 );
	devContext->PSSetShader( pshader->pixelShader, 0, 0 );
	devContext->IASetInputLayout( this->inputLayout );
	devContext->IASetVertexBuffers( 0, 1, &this->vertexbuffer, &stride, &offset );
	devContext->IASetIndexBuffer ( this->indexbuffer, DXGI_FORMAT_R32_UINT, 0 ); //DXGI_FORMAT_R16_UINT

}

void DrawTarget::draw( ID3D11DeviceContext* devContext )
{


	devContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	devContext->DrawIndexed( 6, 0, 0 );

}

bool DeferredRenderer::getDeviceCapabilities( DXGI_MODE_DESC* displayModes, UINT* numOutputs )
{

	UINT numDisplayModes = 0;
	displayModes = 0;
	IDXGIAdapter *IDXGIdev;
	IDXGIOutput *IDXGIout;
	IDXGIFactory1* IDGXIfact1;

	if(FAILED(CreateDXGIFactory1 ( __uuidof(IDXGIFactory1), (void **)&IDGXIfact1 )))
	{
		Logger::getSingleton().logEntry( "DXGI init", "DXGI factory could not be created" );
		return false;
	}

	if(FAILED( IDGXIfact1->EnumAdapters( 0, &IDXGIdev )))
	{
		Logger::getSingleton().logEntry( "DXGI init", "adapter enum failed" );
		return false;
	}
	if(FAILED(IDXGIdev->EnumOutputs ( 0, &IDXGIout )))
	{
		Logger::getSingleton().logEntry( "DXGI init", "output enum failed" );
		return false;
	}
	IDXGIout->GetDisplayModeList ( DXGI_FORMAT_R8G8B8A8_UNORM, NULL, &numDisplayModes, NULL );
	if( numDisplayModes > 0 ) 
	{
		displayModes = new DXGI_MODE_DESC[numDisplayModes];
		IDXGIout->GetDisplayModeList ( DXGI_FORMAT_B8G8R8A8_UNORM, NULL, &numDisplayModes, displayModes );
		*numOutputs = numDisplayModes;
		return true;
	}
	return false;
}

bool DeferredRenderer::initSwapchain( HWND window, UINT width, UINT height, bool windowed )
{

	DXGI_MODE_DESC* displayModes = 0;
	UINT numOutputs;
	
	this->renderTargetWidth = width;
	this->renderTargetHeight = height;
	if(!this->getDeviceCapabilities( displayModes, &numOutputs ))
	{
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "failed to get device caps" );
        return false;
	}
	
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof(sd) );
    
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    //sd.BufferDesc.Format = displayModes[0].Format;
    //sd.BufferDesc.RefreshRate.Numerator = displayModes[0].RefreshRate.Numerator;
    //sd.BufferDesc.RefreshRate.Denominator = displayModes[0].RefreshRate.Denominator;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	sd.BufferDesc.RefreshRate.Denominator = 1; 
	sd.BufferDesc.RefreshRate.Numerator = 0; //60
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = window;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = windowed;

    if( FAILED( D3D11CreateDeviceAndSwapChain( 0, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, 0, 0,
    D3D11_SDK_VERSION, &sd, &swap_chain, &d3dDevice, 0, &immediateContext )))
    {
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "swap chain could not be created" );
        return false;
    }
    return true;
}

void DeferredRenderer::createDepthStencilState()
{

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_REPLACE;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_GREATER; //D3D11_COMPARISON_LESS; D3D11_COMPARISON_ALWAYS


	this->d3dDevice->CreateDepthStencilState( &depthStencilDesc, &depthStencilState );
	
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.StencilEnable = false;
	this->d3dDevice->CreateDepthStencilState( &depthStencilDesc, &depthTestingDisabled );
	
	//shadow volume rendering states
	//first state for front faces
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_REPLACE;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; //D3D11_COMPARISON_LESS; D3D11_COMPARISON_ALWAYS

	this->d3dDevice->CreateDepthStencilState( &depthStencilDesc, &frontShadowVolumeStencilState );
	
/*	//second state for back faces
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS; //D3D11_COMPARISON_LESS; D3D11_COMPARISON_ALWAYS

	this->d3dDevice->CreateDepthStencilState( &depthStencilDesc, &frontShadowVolumeStencilState );*/
	
	this->immediateContext->OMSetDepthStencilState( depthStencilState, 1 );
}

void DeferredRenderer::createAlphablendingState()
{

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof(D3D11_BLEND_DESC));
	
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //D3D11_BLEND_ONE
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	if(FAILED( this->d3dDevice->CreateBlendState( &blendDesc, &alphaBlendingEnable )))
		Logger::getSingleton().logEntry( "Renderer init", "alphablend state not created" );
	
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	
	if(FAILED( this->d3dDevice->CreateBlendState( &blendDesc, &additiveAlphaLightMap )))
		Logger::getSingleton().logEntry( "Renderer init", "alphablend state not created" );	
		
	D3D11_BLEND_DESC blendDesc2;
	ZeroMemory( &blendDesc2, sizeof(D3D11_BLEND_DESC));
	blendDesc2.AlphaToCoverageEnable = false;
	blendDesc2.IndependentBlendEnable = false;
	blendDesc2.RenderTarget[0].BlendEnable = true;
	blendDesc2.RenderTarget[1].BlendEnable = false;
	blendDesc2.RenderTarget[2].BlendEnable = false;
	blendDesc2.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc2.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; //D3D11_BLEND_ONE
	blendDesc2.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc2.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc2.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc2.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	blendDesc2.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	//blendDesc2.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	if(FAILED( this->d3dDevice->CreateBlendState( &blendDesc2, &additiveAlphaBlendingEnable )))
		Logger::getSingleton().logEntry( "Renderer init", "alphablend state not created" );
		
	D3D11_BLEND_DESC blendDesc3;
	ZeroMemory( &blendDesc3, sizeof(D3D11_BLEND_DESC));
	blendDesc3.AlphaToCoverageEnable = false;
	blendDesc3.IndependentBlendEnable = false;
	blendDesc3.RenderTarget[0].BlendEnable = false;
	blendDesc3.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc3.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; //D3D11_BLEND_ONE
	blendDesc3.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc3.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc3.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc3.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc3.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if(FAILED( this->d3dDevice->CreateBlendState( &blendDesc3, &alphaBlendingDisabled )))
		Logger::getSingleton().logEntry( "Renderer init", "alphablend state not created" );

}

bool DeferredRenderer::initRenderTargets()
{
	ID3D11Texture2D* texture = 0;

	if(FAILED( this->swap_chain->GetBuffer( 0, __uuidof( ID3D11Texture2D), ( LPVOID* )&texture )))
		Logger::getSingleton().logEntry( "ERROR","Failed to get buffer backbuffer" );

	HRESULT hr = this->d3dDevice->CreateRenderTargetView( texture, 0, &this->backbuffer );
	if( hr != S_OK ) Logger::getSingleton().logEntry( "ERROR","Cannot create rendertargetview" );
	
	UINT index = 0;
	D3D11_VIEWPORT viewport[3];
 	ZeroMemory( &viewport, sizeof(viewport));
	while( index < 3 )
	{
		viewport[index].Width = (float)this->renderTargetWidth;
		viewport[index].Height = (float)this->renderTargetHeight;
		viewport[index].MinDepth = 0.0f;
		viewport[index].MaxDepth = 1.0f;
		viewport[index].TopLeftX = 0.0f;
		viewport[index].TopLeftY = 0.0f;
		index++;
	}
	this->immediateContext->RSSetViewports( 3, viewport );
	texture->Release();
	return true;
	
}

void DeferredRenderer::initSamplerState()
{

	D3D11_SAMPLER_DESC desc;
	ZeroMemory( &desc, sizeof(desc));
	
    //desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.Filter = D3D11_FILTER_ANISOTROPIC;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MaxAnisotropy = 16;
    desc.MinLOD = 0;
    desc.MaxLOD = D3D11_FLOAT32_MAX;
	
	if(FAILED( this->d3dDevice->CreateSamplerState( &desc, &this->samplerState )))
		Logger::getSingleton().logEntry( "Sampler not created","ERROR" );
		
	this->immediateContext->PSSetSamplers( 0, 1, &this->samplerState );
		
}

void DeferredRenderer::initGBuffer()
{

	this->numRenderTargets = 3;
	this->gBufferRenderTargets = new ID3D11RenderTargetView*[numRenderTargets];
	this->gBufferTextures = new ID3D11ShaderResourceView*[numRenderTargets];
	for( UINT i = 0; i < this->numRenderTargets; i++ )
	{
		DXGI_FORMAT format;
		//if( i == 0 ) format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //
		if( i == 0 ) format = DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UNORM; //color
		//if( i == 1 ) format = DXGI_FORMAT::DXGI_FORMAT_R11G11B10_FLOAT;	//normal
		if( i == 1 ) format = DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
		//if( i == 1 ) format = DXGI_FORMAT_R10G10B10A2_UNORM;
		//if( i == 2 ) format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;	//depth
		if( i == 2 ) format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		//if( i == 2 ) format = DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_FLOAT;
		
		ID3D11Texture2D* texture = 0;

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory( &desc, sizeof(D3D11_TEXTURE2D_DESC));
		
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Width = this->renderTargetWidth;
		desc.Height = this->renderTargetHeight;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		
		if(FAILED(d3dDevice->CreateTexture2D( &desc, 0, &texture )))
		{
			Logger::getSingleton().logEntry( "DeferredRenderer initialization", "failed to create texture for render target" );
			return;
		}
		//d3dDevice->CreateRenderTargetView( texture, 0, &renderTargets[i]);
				D3D11_RENDER_TARGET_VIEW_DESC RTdesc;
		ZeroMemory( &RTdesc, sizeof( D3D11_RENDER_TARGET_VIEW_DESC ));
		
		RTdesc.Format = format;
		RTdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		RTdesc.Texture2D.MipSlice = 1;
		
		if(FAILED(d3dDevice->CreateRenderTargetView( texture, 0, &gBufferRenderTargets[i] )))
		{
			std::stringstream temp;
			temp << "failed to create render target num " << i;
			Logger::getSingleton().logEntry( "DeferredRenderer initialization", temp.str());
			return;
		}
		
		if(FAILED(d3dDevice->CreateShaderResourceView( texture, 0, &gBufferTextures[i] )))
		{
			Logger::getSingleton().logEntry( "DeferredRenderer initialization", "failed to create resource view of rendertarget textures" );
			return;
		}
		texture->Release();
	}
	Logger::getSingleton().logEntry( "DeferredRenderer initialization", "successfully created GBuffer rendertargets" );

}

void DeferredRenderer::initLightMapRT()
{
		
	ID3D11Texture2D* texture = NULL;
	shadowRenderer = new ShadowRenderer;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory( &desc, sizeof(D3D11_TEXTURE2D_DESC));
	DXGI_FORMAT format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //DXGI_FORMAT::DXGI_FORMAT_R16G16B16A16_UNORM;
	
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Width = this->renderTargetWidth;
	desc.Height = this->renderTargetHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	
	if(FAILED(d3dDevice->CreateTexture2D( &desc, 0, &texture )))
	{
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "failed to create texture for render target" );
		return;
	}
	D3D11_RENDER_TARGET_VIEW_DESC RTdesc;
	ZeroMemory( &RTdesc, sizeof( D3D11_RENDER_TARGET_VIEW_DESC ));
	
	RTdesc.Format = format;
	RTdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	RTdesc.Texture2D.MipSlice = 1;
	
	if(FAILED(d3dDevice->CreateRenderTargetView( texture, 0, &lightMapRT )))
	{
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "light map render target creation failed" );
		return;
	}
	
	if(FAILED(d3dDevice->CreateShaderResourceView( texture, 0, &lightMapTexture )))
	{
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "failed to create resource view of light map texture" );
		return;
	}
	texture->Release();

}

bool DeferredRenderer::initDepthbuffer()
{

	ID3D11Texture2D* depthbuffer = NULL;

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory( &desc, sizeof(D3D11_TEXTURE2D_DESC) );
	
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Width = this->renderTargetWidth;
	desc.Height = this->renderTargetHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	d3dDevice->CreateTexture2D ( &desc, NULL, &depthbuffer );

	D3D11_DEPTH_STENCIL_VIEW_DESC descDS;
	ZeroMemory( &descDS, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	
	descDS.Format = desc.Format;
	descDS.Texture2D.MipSlice = 0;
	descDS.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;


	if(FAILED( d3dDevice->CreateDepthStencilView ( depthbuffer, &descDS, &this->depthBuffer )))
	{
		Logger::getSingleton().logEntry( "DeferredRenderer initialization", "Cannot create depthStencilBuffer" );
		return false;
	}
	depthbuffer->Release ();
	bool isSuccess = TRUE;
	return isSuccess;
}

void DeferredRenderer::createDeferredRenderer( HWND window, RendererSettings& settings )
{

	this->initSwapchain( window, settings.viewWidth, settings.viewHeight, settings.windowed );
	this->initDepthbuffer();
	this->initRenderTargets();
	if( settings.mode == RendererMode::Deferred )
	{
		this->initGBuffer();
		this->initLightMapRT();
		this->drawTarget = new DrawTarget;
		this->loadShaders();
		this->initViewProjectionBuffer();
	}
	this->setBackbuffer();
	
	this->createDepthStencilState();
	this->createRasterizerState();
	this->createAlphablendingState();
	this->initLightBuffer();
	this->initSamplerState();
	this->lightRenderer = new LightRenderer( this->d3dDevice );

}

void DeferredRenderer::enableBackfaceCulling( boolean enable )
{

	if( enable ) this->immediateContext->RSSetState( defaultRasterizerState );
	else this->immediateContext->RSSetState( noClippingRasterizerState );

}

void DeferredRenderer::createRasterizerState()
{

	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory ( &rasterDesc, sizeof(rasterDesc));
	
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_BACK; //D3D11_CULL_NONE; D3D11_CULL_BACK
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = false;
	
	this->d3dDevice->CreateRasterizerState( &rasterDesc, &defaultRasterizerState );
	this->immediateContext->RSSetState( defaultRasterizerState );
	
	ZeroMemory ( &rasterDesc, sizeof(rasterDesc));
	
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE; //D3D11_CULL_NONE; D3D11_CULL_BACK
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = false;
	
	this->d3dDevice->CreateRasterizerState( &rasterDesc, &noClippingRasterizerState );

}

void DeferredRenderer::render( Renderable* renderable )
{

	renderable->draw( this->immediateContext );
	
}

void DeferredRenderer::setRendererResources( RendererResource* resource )
{

	resource->setRendererResources( this->immediateContext );

}

void DeferredRenderer::setViewport( UINT numViewports )
{

	D3D11_VIEWPORT viewport;
 	ZeroMemory( &viewport, sizeof(viewport));
	viewport.Width = (FLOAT)this->renderTargetWidth;
	viewport.Height = (FLOAT)this->renderTargetHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	
	this->immediateContext->RSSetViewports( numViewports, &viewport );

}

bool DeferredRenderer::loadShaders()
{

	this->composerVshader = ShaderManager::getSingleton().getVertexShader( "composer.vsh" );
	this->composerPshader = ShaderManager::getSingleton().getPixelShader( "composer.psh" );
	this->directionalLightVshader = ShaderManager::getSingleton().getVertexShader( "directionalLight.vsh" );
	this->directionalLightPshader = ShaderManager::getSingleton().getPixelShader( "directionalLight.psh" );
	this->blurVShader = ShaderManager::getSingleton().getVertexShader( "blurVShader.vsh" );
	this->blurPShader = ShaderManager::getSingleton().getPixelShader( "blurPShader.psh" );
	return true;
}

ID3D11Device* DeferredRenderer::getDevice()
{

	return this->d3dDevice;

}

void DeferredRenderer::enableDepthTesting( bool enable )
{

	if( enable ) this->immediateContext->OMSetDepthStencilState( this->depthStencilState, 0 );
	else this->immediateContext->OMSetDepthStencilState( this->depthTestingDisabled, 0 );
}

void DeferredRenderer::setAlphaBlendingState( AlphaBlendingState state )
{

	if( state == AlphaBlendingState::AlphaBlendEnabled )
	{
		float blendFactors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		immediateContext->OMSetBlendState( this->alphaBlendingEnable, blendFactors, 0xffffffff );
	}
	if( state == AlphaBlendingState::AlphaBlendAdditive )
	{
		float blendFactors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		immediateContext->OMSetBlendState( this->additiveAlphaBlendingEnable, blendFactors, 0xffffffff );
	}
	if( state == AlphaBlendingState::AlphaBlendDisabled )
	{
		float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		immediateContext->OMSetBlendState( this->alphaBlendingDisabled, blendFactors, 0xffffffff );
	}
}

void DeferredRenderer::setGBuffer()
{

	this->immediateContext->OMSetRenderTargets( numRenderTargets, this->gBufferRenderTargets, this->depthBuffer );
	float color[] = { 0.0f,0.0f,0.0f,0.0f };
	immediateContext->ClearRenderTargetView( this->gBufferRenderTargets[0], color );
	float normals[] = { 0.5f,0.5f,0.5f, 0.0f };
	//float normals[] = { 1.0f,1.0f,1.0f };
	immediateContext->ClearRenderTargetView( this->gBufferRenderTargets[1], normals );
	float depth[] = { 1.0f, 0.0f, 0.0f, 0.0f };
	immediateContext->ClearRenderTargetView( this->gBufferRenderTargets[2], depth );
	immediateContext->ClearDepthStencilView( depthBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	
	//setViewport(3);

}

void DeferredRenderer::setBackbuffer()
{
	ID3D11RenderTargetView* views[3];
	views[0] = this->backbuffer;
	views[1] = 0;
	views[2] = 0;
	this->immediateContext->OMSetRenderTargets( 3, views, 0 );
	float color[] = { 0.0f,0.0f,0.0f,0.0f };
	immediateContext->ClearRenderTargetView ( this->backbuffer, color );
	//immediateContext->ClearDepthStencilView ( depthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0 );
	//setViewport(1);

}

void DeferredRenderer::setLightMapRT()
{
	ID3D11RenderTargetView* views[3];
	views[0] = this->lightMapRT;
	views[1] = 0;
	views[2] = 0;
	this->immediateContext->OMSetRenderTargets( 3, views, 0 );
	float color[] = { 0.0f,0.0f,0.0f,0.0f };
	immediateContext->ClearRenderTargetView ( this->lightMapRT, color );
	//immediateContext->ClearDepthStencilView ( depthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0 );	

}

XMFLOAT2 DeferredRenderer::getRenderTargetSize()
{

	return XMFLOAT2((float)this->renderTargetWidth, (float)this->renderTargetHeight );

}

void DeferredRenderer::renderImmediateBegin()
{

	float color[] = { 0.0f,0.7f,0.7f,0.0f };
	immediateContext->ClearRenderTargetView ( this->backbuffer, color );
	immediateContext->ClearDepthStencilView ( depthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0 );

}

void DeferredRenderer::renderImmediateEnd()
{

	//swap_chain->Present( 0, 0 );
	//this->setBackbuffer();
/*	this->immediateContext->IASetInputLayout( this->lightInputLayout );
	this->immediateContext->VSSetShader( this->vShader, 0, 0 );
	this->immediateContext->PSSetShader( this->pShader, 0, 0 );
	this->immediateContext->PSSetShaderResources( 0, this->numRenderTargets, this->gBufferTextures );
	if(!lights.empty())
	{
		std::list<Light*>::iterator iter = lights.begin();
		while( iter != lights.end())
		{
			(*iter)->setBuffers( this->immediateContext );
			(*iter)->draw( this->immediateContext );
			iter++;
		}
	}*/
	swap_chain->Present( 0, 0 );

}

void DeferredRenderer::renderDeferredBegin()
{

	this->setGBuffer();
	this->setViewProjectionMatrices();
	
}

void DeferredRenderer::renderBlur()
{

	ID3D11ShaderResourceView* views[4];
	views[0] = this->gBufferTextures[0];
	views[1] = this->gBufferTextures[1];
	views[2] = this->gBufferTextures[2];
	views[3] = this->lightMapTexture;
	this->drawTarget->setResources( this->immediateContext, this->blurPShader, this->blurVShader );
	this->immediateContext->PSSetShaderResources( 0, this->numRenderTargets + 1, views );
	//this->immediateContext->VSSetConstantBuffers( 0, 1, &this->lightBuffer );
	//this->immediateContext->PSSetConstantBuffers( 1, 1, &this->lightBuffer );
	this->setViewProjectionMatrices();
	this->drawTarget->draw( this->immediateContext );	

}

void DeferredRenderer::renderShadowPass()
{

	

}

void DeferredRenderer::renderDeferredEnd()
{

	this->setBackbuffer();
	//this->immediateContext->PSSetConstantBuffers( 0, 1, &this->lightBuffer );
	ID3D11ShaderResourceView* views[4];
	views[0] = this->gBufferTextures[0];
	views[1] = this->gBufferTextures[1];
	views[2] = this->gBufferTextures[2];
	views[3] = this->lightMapTexture;
	
	this->drawTarget->setResources( this->immediateContext, this->composerPshader, this->composerVshader );
	this->immediateContext->PSSetShaderResources( 0, this->numRenderTargets + 1, views );
	this->drawTarget->draw( this->immediateContext );
	
}

void DeferredRenderer::initLightBuffer()
{

/*	D3D11_BUFFER_DESC desc;
	ZeroMemory( &desc, sizeof( D3D11_BUFFER_DESC ));
	
	desc.ByteWidth = sizeof(DirectionalLightBuffer);
	desc.Usage = D3D11_USAGE_DYNAMIC; 
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	
	if(FAILED( this->d3dDevice->CreateBuffer( &desc, 0, &this->lightBuffer )))
		Logger::getSingleton().logEntry( "SceneNode", "failed to create constantbuffer" );*/
		
}

void DeferredRenderer::initViewProjectionBuffer()
{

	D3D11_BUFFER_DESC desc;
	ZeroMemory( &desc, sizeof( D3D11_BUFFER_DESC ));
	
	desc.ByteWidth = sizeof(CameraMatrixBuffer);
	desc.Usage = D3D11_USAGE_DYNAMIC; 
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	
	if(FAILED( this->d3dDevice->CreateBuffer( &desc, 0, &this->viewProjectionBuffer )))
		Logger::getSingleton().logEntry( "SceneNode", "failed to create constantbuffer" );

}

void DeferredRenderer::drawDirectionalLight( const XMFLOAT3& direction, const XMFLOAT3& sunPosition, 
const XMFLOAT3& color, float lightIntensity, float ambientIntensity )
{

	lightRenderer->drawDirectionalLight( this->immediateContext, XMFLOAT2((float)this->renderTargetWidth, (float)this->renderTargetHeight ),
		direction, color, lightIntensity, ambientIntensity, sunPosition );
	
	this->drawTarget->setResources( this->immediateContext, this->directionalLightPshader, this->directionalLightVshader );
	this->immediateContext->PSSetShaderResources( 0, this->numRenderTargets, this->gBufferTextures );
	this->drawTarget->draw( this->immediateContext );

}

void DeferredRenderer::drawPointLight( const XMFLOAT3& position, float radius, const XMFLOAT3& color, float lightIntensity )
{

	this->immediateContext->PSSetShaderResources( 0, this->numRenderTargets, this->gBufferTextures );
	lightRenderer->drawPointLight( this->immediateContext, position, XMFLOAT2((float)this->renderTargetWidth, (float)this->renderTargetHeight ),
	radius, color, lightIntensity );
}

void DeferredRenderer::renderLightPassBegin()
{

	this->setLightMapRT();
	//this->setViewProjectionMatrices();
	this->setInverseViewProjectionMatrices();
	float blendFactors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	immediateContext->OMSetBlendState( this->additiveAlphaLightMap, blendFactors, 0xffffffff );
	//immediateContext->OMSetDepthStencilState( this->depthStencilState, 0 );
	//this->setAlphaBlendingState( AlphaBlendingState::AlphaBlendAdditive );

}

void DeferredRenderer::renderLightPassEnd()
{

	this->setAlphaBlendingState( AlphaBlendingState::AlphaBlendEnabled );
	this->setViewProjectionMatrices();

}

void DeferredRenderer::renderDeferredPresent()
{

	swap_chain->Present( 0, 0 );

}

void DeferredRenderer::setViewMatrix( const XMFLOAT4X4& view, const XMFLOAT3& cameraPosition )
{

	//XMMATRIX mView = XMLoadFloat4x4( &view );
	//this->currentCameraBuffer.viewMatrix = mView;
	this->viewMatrix = view;
	//this->currentCameraBuffer.position = XMFLOAT4( cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f );
	this->position = XMFLOAT4( cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f );

}

void DeferredRenderer::setProjectionMatrix( const XMFLOAT4X4& projection )
{

	//XMMATRIX mProjection = XMLoadFloat4x4( &projection );
	//this->currentCameraBuffer.projectionMatrix = mProjection;
	this->projectionMatrix = projection;

}

void DeferredRenderer::setViewProjectionMatrices( bool vshader, bool pshader )
{

	D3D11_MAPPED_SUBRESOURCE mappedResource;

	if(FAILED( this->immediateContext->Map( this->viewProjectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource )))
		return;
	CameraMatrixBuffer* buffer = (CameraMatrixBuffer*)mappedResource.pData;
/*	buffer->projectionMatrix = XMMatrixTranspose( this->currentCameraBuffer.projectionMatrix );
	buffer->viewMatrix = XMMatrixTranspose( this->currentCameraBuffer.viewMatrix );
	buffer->position = this->currentCameraBuffer.position;*/
	XMMATRIX mProjection = XMLoadFloat4x4( &projectionMatrix );
	mProjection = XMMatrixTranspose( mProjection );
	XMStoreFloat4x4( &buffer->projectionMatrix, mProjection );
	XMMATRIX mView = XMLoadFloat4x4( &viewMatrix );
	mView = XMMatrixTranspose( mView );
	XMStoreFloat4x4( &buffer->viewMatrix, mView );
	buffer->position = this->position;
	this->immediateContext->Unmap( this->viewProjectionBuffer, 0 );
	if( vshader ) this->immediateContext->VSSetConstantBuffers( 0, 1, &this->viewProjectionBuffer );	
	if( pshader ) this->immediateContext->PSSetConstantBuffers( 0, 1, &this->viewProjectionBuffer );	

}

void DeferredRenderer::setInverseViewProjectionMatrices( bool vshader, bool pshader )
{

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	XMVECTOR det;

	if(FAILED( this->immediateContext->Map( this->viewProjectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource )))
		return;
	CameraMatrixBuffer* buffer = (CameraMatrixBuffer*)mappedResource.pData;
/*	buffer->projectionMatrix = XMMatrixTranspose( XMMatrixInverse( &det, XMMatrixMultiply( this->currentCameraBuffer.viewMatrix, this->currentCameraBuffer.projectionMatrix )));
	buffer->viewMatrix = XMMatrixTranspose( XMMatrixMultiply( this->currentCameraBuffer.viewMatrix, this->currentCameraBuffer.projectionMatrix ));
	buffer->position = this->currentCameraBuffer.position;*/
	XMMATRIX mView = XMLoadFloat4x4( &viewMatrix );
	XMMATRIX mProjection = XMLoadFloat4x4( &projectionMatrix );
	//mProjection = XMMatrixInverse( &det, mProjection );
	//buffer->projectionMatrix = XMMatrixTranspose( mProjection );
	XMMATRIX mInvViewProj = XMMatrixTranspose( XMMatrixInverse( &det, XMMatrixMultiply( mView, mProjection )));
	XMStoreFloat4x4( &buffer->projectionMatrix, mInvViewProj );
	XMMATRIX mViewProj = XMMatrixTranspose( XMMatrixMultiply( mView, mProjection ));
	XMStoreFloat4x4( &buffer->viewMatrix, mViewProj );
	buffer->position = this->position;
	this->immediateContext->Unmap( this->viewProjectionBuffer, 0 );
	if( vshader ) this->immediateContext->VSSetConstantBuffers( 0, 1, &this->viewProjectionBuffer );	
	if( pshader ) this->immediateContext->PSSetConstantBuffers( 0, 1, &this->viewProjectionBuffer );	

}

void DeferredRenderer::renderQueue( RenderQueue* queue )
{

	queue->draw( this->immediateContext );

}