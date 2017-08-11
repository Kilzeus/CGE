#pragma once
//#include<directXMath.h>
#include<D3D11.h>
#include<DXGI.h>
#include"Device.h"
#include<list>

namespace Renderer
{
	class D3D11Device : public Device
	{
		friend class D3D11Core;
		friend class D3D11RenderContext;
		ID3D11Device* device;
		ID3D11DeviceContext* iRenderContext;
		RenderContext* renderContext;
		IDXGISwapChain* swapChain;
		ID3D11DepthStencilView* depthStencil;
		D3D_FEATURE_LEVEL featureLevel;
		RenderTargetView* backBuffer;
		Float2 screenSpaceTopLeft;
		ID3D11SamplerState* defaultSamplerState;
		Uint2 resolution;

		D3D11Device(
			const DeviceProperties& properties,
			ID3D11Device* device,
			ID3D11DeviceContext* renderContext,
			IDXGISwapChain* swapChain,
			D3D_FEATURE_LEVEL featureLevel,
			ID3D11DepthStencilView* depthStencil,
			ID3D11RenderTargetView* backBufferView
		);
		void createDefaultSampler();
	public:
		IndexBuffer* createIndexBuffer(UINT byteSize,IndexDataFormat format);
		VertexBuffer* crateVertexBuffer(UINT byteSize,bool dynamic=false);
		Texture* createTexture(Resource* resource,Uint2 dimensions,
			TextureFormat format, UINT arraySize = 1, bool writeAcces = false,
			bool renderTarget = false);
		RenderTargetView* createRenderTarget(Texture* resource);
		//shaders
		VertexShader* createVertexShader(Resource* resource,VertexFormat* format);
		FragmentShader* createFragmentShader(Resource* resource);
		GeometryShader* createGeometryShader(Resource* resource);
		TessellationControlShader* createTessellationConrolShader(Resource* resource);
		TessellationEvaluationShader* createTessellationEvaluationShader(Resource* resource);
		//end shaders
		RenderContext* getRenderContext();
		GPUBuffer* createGPUBuffer(UINT byteSize);
		Resource* compileShaderFromFile(
			const std::wstring& filename,std::string shaderProfile
		);
		VertexFormat* createVertexFormat();
		RenderTargetView* getBackBuffer();
		const Float2& getScreenSpaceTopLeft();
		const Uint2& getResolution();
	};
}