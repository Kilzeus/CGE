#include "D3D11RenderContext.h"
#include"D3D11RenderTargetView.h"
#include"D3D11GPUBuffer.h"
#include"D3D11VertexBuffer.h"
#include"D3D11IndexBuffer.h"
#include"D3D11VertexShader.h"
#include"D3D11FragmentShader.h"
#include"D3D11GeometryShader.h"
#include"D3D11VertexFormat.h"
#include"D3D11Texture.h"

using namespace Renderer;
D3D11RenderContext::D3D11RenderContext(
	ID3D11Device* device,
	ID3D11DeviceContext* renderContext,
	ID3D11DepthStencilView* depthStencil,
	IDXGISwapChain* swapChain
):renderContext(renderContext),depthStencil(depthStencil),
swapChain(swapChain)
{
	initDepthStencilStates(device);
	initAlphaTestingStates(device);
	initBackFaceCullingStates(device);
}


void D3D11RenderContext::setViewports(UINT num)
{
	if (num > 1)
	{
		D3D11_VIEWPORT* viewports = new D3D11_VIEWPORT[num];
		for (int i = 0; i < num; i++)
		{
			viewports[i] = viewport;
		}
		renderContext->RSSetViewports(num, viewports);
		delete[] viewports;
	}
	else renderContext->RSSetViewports(1, &viewport);
}


void D3D11RenderContext::initDepthStencilStates(ID3D11Device* device)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false;
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


	HRESULT result = device->CreateDepthStencilState( &depthStencilDesc, &depthTestingEnabled );
	
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.StencilEnable = false;
	result = device->CreateDepthStencilState( &depthStencilDesc, &depthTestingDisabled );
}


bool D3D11RenderContext::fillTexture(Texture* texture, Resource* data)
{
	D3D11Texture* d3d11Texture = (D3D11Texture*)texture;
	if (d3d11Texture->usage == D3D11_USAGE_DEFAULT)
	{
		renderContext->UpdateSubresource(d3d11Texture->texture, 0, 0, data->getData(), data->getPitch(),0);
	}
	else if (d3d11Texture->usage == D3D11_USAGE_DYNAMIC)
	{
		D3D11_MAPPED_SUBRESOURCE descr;
		ZeroMemory(&descr, sizeof(D3D11_MAPPED_SUBRESOURCE));
		descr.pData = data->getData();
		descr.RowPitch = data->getPitch();
		renderContext->Map(d3d11Texture->texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &descr);
	}
	return true;
}


void D3D11RenderContext::generateMipmaps(Texture* texture)
{
	D3D11Texture* tex = (D3D11Texture*)texture;
	renderContext->GenerateMips(tex->shaderView);
}


void D3D11RenderContext::initAlphaTestingStates(ID3D11Device* device)
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory( &blendDesc, sizeof(D3D11_BLEND_DESC));
	
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	device->CreateBlendState(&blendDesc,&alphaBlendingEnable);
		
	ZeroMemory( &blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState( &blendDesc,&additiveAlphaBlendingEnable );
		
	ZeroMemory( &blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = false;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState( &blendDesc, &alphaBlendingDisabled );
}


void D3D11RenderContext::setAlphaBlendingState(AlphaBlendingState state)
{
	float blendFactors[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	if(state==AlphaBlendingState::AlphaBlendNormal)
		renderContext->OMSetBlendState(alphaBlendingEnable,blendFactors,0xffffffff);
	if(state==AlphaBlendingState::AlphaBlendAdditive)
		renderContext->OMSetBlendState(additiveAlphaBlendingEnable,blendFactors,0xffffffff);
	if(state==AlphaBlendingState::AlphaBlendDisabled)
		renderContext->OMSetBlendState(alphaBlendingDisabled,blendFactors,0xffffffff);
}


void D3D11RenderContext::setRenderTarget(RenderTargetView* renderTarget)
{
	numRenderTargets = 1;
	this->renderTargets[0] = ((D3D11RenderTargetView*)renderTarget)->view;
	renderContext->OMSetRenderTargets(
		1,renderTargets,depthStencil
	);
}

/**
	Sets renderTargets.
*/
void D3D11RenderContext::setRenderTargets(RenderTargetView** renderTarget,UINT numRenderTargets)
{
	if (numRenderTargets > this->numRenderTargets) setViewports(numRenderTargets);
	this->numRenderTargets = numRenderTargets;
	for(int i=0;i<numRenderTargets;i++)
	{
		renderTargets[i] = ((D3D11RenderTargetView*)renderTarget[i])->view;
	}
	renderContext->OMSetRenderTargets(
		numRenderTargets,renderTargets,depthStencil
	);
}


void D3D11RenderContext::unbindRenderTargets()
{
	ID3D11RenderTargetView* renderTargets[8];
	for (int i = 0; i < 8; i++)
	{
		renderTargets[i] = 0;
	}
	renderContext->OMSetRenderTargets(8, renderTargets, 0);
}


void D3D11RenderContext::setTexture(UINT slot,Texture* texture)
{
	renderContext->PSSetShaderResources(slot,1,&((D3D11Texture*)texture)->shaderView);
}


void D3D11RenderContext::enableDepthTesting(bool state)
{
	if(state) 
		renderContext->OMSetDepthStencilState(
			depthTestingEnabled,0
		);
	else
		renderContext->OMSetDepthStencilState(
			depthTestingDisabled,0
		);
}


void D3D11RenderContext::setBackbufferRenderTarget()
{
	numRenderTargets = 1;
	this->renderTargets[0] = ((D3D11RenderTargetView*)backBuffer)->view;
	renderContext->OMSetRenderTargets(
		1, renderTargets, depthStencil
		);
}


void D3D11RenderContext::enableBackfaceCulling(bool state)
{
	if(state) 
		renderContext->RSSetState(
			backFaceCullingEnabled
		);
	else
		renderContext->RSSetState(
			backFaceCullingDisabled
		);
}


void D3D11RenderContext::initBackFaceCullingStates(ID3D11Device* device)
{
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc,sizeof(rasterDesc));
	
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_BACK; //D3D11_CULL_NONE; D3D11_CULL_BACK
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = true;
	
	device->CreateRasterizerState(&rasterDesc,&backFaceCullingEnabled);
	
	ZeroMemory(&rasterDesc,sizeof(rasterDesc));
	
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_NONE; //D3D11_CULL_NONE; D3D11_CULL_BACK
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
	rasterDesc.DepthClipEnable = false;
	
	device->CreateRasterizerState(&rasterDesc,&backFaceCullingDisabled);
	renderContext->RSSetState(backFaceCullingDisabled);
}

/**
	Sets the colors the render targets are set when they are cleared. There must be at least as
	many colors as there are render targets. If there are more colors than render targets then
	extra colors will not be used. 
*/
void D3D11RenderContext::setRenderTargetClearColors(const std::vector<float*>& colors)
{
	this->colors = colors;
}

/**
	Set the topology of primitives to render.
*/
void D3D11RenderContext::setPrimitiveTopology(PrimitiveTopology state)
{
	if(state==PrimitiveTopology::PointList ) 
		renderContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	else if(state==PrimitiveTopology::TriangleList ) 
		renderContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	else 
		renderContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}


void D3D11RenderContext::setRenderTargetClearColor(UINT index, float* colors)
{
	this->colors[index] = colors;
}

/**
	Clears render targets to a predefined color. Also clears depth and stencils.
*/
void D3D11RenderContext::renderBegin(bool clearDepth)
{
	for(int i=0;i<numRenderTargets;i++)
	{
		renderContext->ClearRenderTargetView(
			renderTargets[i], colors[i]
		);
	}
	if (clearDepth) 
		renderContext->ClearDepthStencilView(
			depthStencil,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,1.f,0);
}


void D3D11RenderContext::renderEnd()
{
	HRESULT result = swapChain->Present(0,0);
}


void D3D11RenderContext::setGPUBuffer(UINT slot,GPUBuffer* buffer)
{
	renderContext->VSSetConstantBuffers(slot,1,&((D3D11GPUBuffer*)buffer)->buffer);
	renderContext->PSSetConstantBuffers(slot,1,&((D3D11GPUBuffer*)buffer)->buffer);
	renderContext->GSSetConstantBuffers(slot,1,&((D3D11GPUBuffer*)buffer)->buffer);
}


void D3D11RenderContext::setVertexBuffer(VertexBuffer* buffer)
{
	if(buffer)
	{
		UINT offset = 0;
		UINT stride = buffer->getVertexByteSize();
		renderContext->IASetVertexBuffers(
			0,1,&((D3D11VertexBuffer*)buffer)->buffer,&stride,&offset
		);
		numVerticesBound = buffer->getNumVertices();
	}
	else
	{
		renderContext->IASetVertexBuffers(
			0,0,0,0,0
		);
	}
}


void D3D11RenderContext::setIndexBuffer(IndexBuffer* buffer)
{
	renderContext->IASetIndexBuffer(
		((D3D11IndexBuffer*)buffer)->buffer,((D3D11IndexBuffer*)buffer)->d3dFormat,0
	);
	numIndicesBound = buffer->getNumIndices();
}


void D3D11RenderContext::setVertexShader(VertexShader* shader)
{
	renderContext->VSSetShader(
		((D3D11VertexShader*)shader)->shader,0,0
	);
}


void D3D11RenderContext::setFragmentShader(FragmentShader* shader)
{
	renderContext->PSSetShader(
		((D3D11FragmentShader*)shader)->shader,0,0
	);
}


void D3D11RenderContext::setGeometryShader(GeometryShader* shader)
{
	renderContext->GSSetShader(
		((D3D11GeometryShader*)shader)->shader,0,0
	);
}


void D3D11RenderContext::setVertexFormat(VertexFormat* format)
{
	renderContext->IASetInputLayout(
		((D3D11VertexFormat*)format)->inputLayout
	);
}


void D3D11RenderContext::draw()
{
	renderContext->Draw(numVerticesBound,0);
}


void D3D11RenderContext::drawIndexed()
{
	renderContext->DrawIndexed(numIndicesBound,0,0);
}


void D3D11RenderContext::drawInstanced()
{
	renderContext->DrawInstanced(
		numVerticesBound,numInstances,0,0
	);
}


void D3D11RenderContext::drawIndexedInstanced()
{

}


void D3D11RenderContext::setInstanceBuffer(InstanceBuffer* buffer)
{
	
}