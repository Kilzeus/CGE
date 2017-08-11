#pragma once
#include"IndexBuffer.h"
#include"VertexBuffer.h"
#include"Texture.h"
#include"VertexShader.h"
#include"GeometryShader.h"
#include"FragmentShader.h"
#include"RenderTargetView.h"
#include"RenderContext.h"
#include"TessellationControlShader.h"
#include"TessellationEvaluationShader.h"
namespace Renderer
{

	struct DeviceProperties
	{
		Uint2 resolution;
		bool fullScreen;
		bool vSync;
		class RenderWindow* window;
	};
	/*
		used for resource creation
	*/
	class Device
	{
		DeviceProperties properties;
	public:
		Device(const DeviceProperties& properties) :properties(properties) {}
		const DeviceProperties& getProperties() {
			return properties;
		}
		virtual IndexBuffer* createIndexBuffer(UINT byteSize,IndexDataFormat format)=0;
		virtual VertexBuffer* crateVertexBuffer(UINT byteSize,bool dynamic=false)=0;
		virtual Texture* createTexture(
			Resource* resource,Uint2 dimensions,TextureFormat format,
			UINT arraySize=1, bool writeAcces=false, bool renderTarget=false
		)=0;
		virtual RenderTargetView* createRenderTarget(Texture* resource)=0;
		//create shaders
		virtual VertexShader* createVertexShader(Resource* resource,VertexFormat* format)=0;
		virtual FragmentShader* createFragmentShader(Resource* resource)=0;
		virtual GeometryShader* createGeometryShader(Resource* resource)=0;
		virtual TessellationControlShader* createTessellationConrolShader(Resource* resource) = 0;
		virtual TessellationEvaluationShader* createTessellationEvaluationShader(Resource* resource) = 0;
		//end shaders
		virtual RenderContext* getRenderContext()=0;
		virtual GPUBuffer* createGPUBuffer(UINT byteSize)=0;
		virtual Resource* compileShaderFromFile(
			const std::wstring& filename,std::string shaderProfile
		)=0;
		virtual VertexFormat* createVertexFormat()=0;
		virtual RenderTargetView* getBackBuffer()=0;
		virtual const Float2& getScreenSpaceTopLeft() = 0;
		virtual const Uint2& getResolution() = 0;
	};
}