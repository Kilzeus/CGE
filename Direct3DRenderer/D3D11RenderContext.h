#pragma once
#include "rendercontext.h"
#include<d3d11.h>
namespace Renderer
{
	class D3D11RenderContext : public RenderContext
	{
		friend class D3D11Device;
		ID3D11DeviceContext* renderContext;
		ID3D11DepthStencilView* depthStencil;
		ID3D11DepthStencilState* depthTestingEnabled;
		ID3D11DepthStencilState* depthTestingDisabled;
		ID3D11RasterizerState* backFaceCullingEnabled;
		ID3D11RasterizerState* backFaceCullingDisabled;

		ID3D11BlendState* alphaBlendingEnable;
		ID3D11BlendState* additiveAlphaBlendingEnable;
		ID3D11BlendState* alphaBlendingDisabled;

		ID3D11RenderTargetView* renderTargets[8];
		UINT numRenderTargets;
		IDXGISwapChain* swapChain;
		UINT numVerticesBound;
		UINT numIndicesBound;
		UINT numInstances;
		std::vector<float*> colors;
		D3D11_VIEWPORT viewport;
		RenderTargetView* backBuffer;

		void setViewports(UINT num);
		void initDepthStencilStates(ID3D11Device* device);
		void initBackFaceCullingStates(ID3D11Device* device);
		void initAlphaTestingStates(ID3D11Device* device);
		D3D11RenderContext(
			ID3D11Device* device,
			ID3D11DeviceContext* renderContext,
			ID3D11DepthStencilView* depthStencil,
			IDXGISwapChain* swapChain
		);
	public:
		void setRenderTarget(RenderTargetView* renderTarget);
		void setRenderTargets(RenderTargetView** renderTarget,UINT RenderTargetCount);
		void setRenderTargetClearColor(UINT index, float* colors);
		void setRenderTargetClearColors(const std::vector<float*>& colors);
		RenderTargetView* getBackBuffer();
		void generateMipmaps(Texture* texture);
		void enableDepthTesting(bool state);
		void enableBackfaceCulling(bool state);
		void setAlphaBlendingState(AlphaBlendingState state);
		void setPrimitiveTopology(PrimitiveTopology state);
		void renderBegin(bool clearDepth = true);
		void renderEnd();
		void setGPUBuffer(UINT slot,GPUBuffer* buffer);
		void setVertexBuffer(VertexBuffer* buffer);
		void setIndexBuffer(IndexBuffer* buffer);
		void setInstanceBuffer(InstanceBuffer* buffer);
		void setVertexShader(VertexShader* shader);
		void setFragmentShader(FragmentShader* shader);
		void setGeometryShader(GeometryShader* shader);
		void setVertexFormat(VertexFormat* format);
		void setTexture(UINT slot,Texture* texture);
		void draw();
		void drawIndexed();
		void drawInstanced();
		void drawIndexedInstanced();
		bool fillTexture(Texture* texture, Resource* data);
		void setBackbufferRenderTarget();
		void unbindRenderTargets();
	};
}
