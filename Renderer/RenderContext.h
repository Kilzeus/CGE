#pragma once
#include"GPUBuffer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexShader.h"
#include"FragmentShader.h"
#include"GeometryShader.h"
#include"RenderTargetView.h"
#include"InstanceBuffer.h"
#include"VertexFormat.h"
namespace Renderer
{
	/* used for rendering, state changes etc.
	*/
	enum AlphaBlendingState{ AlphaBlendDisabled, AlphaBlendNormal, AlphaBlendAdditive };
	enum PrimitiveTopology{ TriangleStrip, TriangleList, PointList };
	class RenderContext
	{
	public:
		//render targets
		virtual void setRenderTarget(RenderTargetView* renderTarget)=0;
		virtual void setRenderTargets(RenderTargetView** renderTarget,UINT RenderTargetCount)=0;
		virtual void setRenderTargetClearColor(UINT index, float* colors) = 0;
		virtual void setRenderTargetClearColors(const std::vector<float*>& colors) = 0;
		virtual void setBackbufferRenderTarget() = 0;
		virtual void unbindRenderTargets() = 0;
		virtual void generateMipmaps(Texture* texture) = 0;
		//states
		virtual void enableDepthTesting(bool state)=0;
		virtual void enableBackfaceCulling(bool state)=0;
		virtual void setAlphaBlendingState(AlphaBlendingState state)=0;
		virtual void setPrimitiveTopology(PrimitiveTopology state)=0;
		//rendering
		virtual void renderBegin(bool clearDepth=true)=0;
		virtual void renderEnd()=0;
		virtual void setGPUBuffer(UINT slot,GPUBuffer* buffer)=0;
		virtual void setVertexBuffer(VertexBuffer* buffer)=0;
		virtual void setIndexBuffer(IndexBuffer* buffer)=0;
		virtual void setInstanceBuffer(InstanceBuffer* buffer)=0;
		virtual void setVertexShader(VertexShader* shader)=0;
		virtual void setFragmentShader(FragmentShader* shader)=0;
		virtual void setGeometryShader(GeometryShader* shader)=0;
		virtual void setVertexFormat(VertexFormat* format)=0;
		virtual void setTexture(UINT slot,Texture* texture)=0;
		virtual void draw()=0;
		virtual void drawIndexed()=0;
		virtual void drawInstanced()=0;
		virtual void drawIndexedInstanced()=0;
		bool fillTexture(Texture* texture, Resource* data);
	};
}
