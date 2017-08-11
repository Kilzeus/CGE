#pragma once
#include"RenderState.h"
#include"Material.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"InstanceBuffer.h"
#include<vector>
namespace RenderFramework
{
	class RenderOperation
	{
		friend class RenderQueue;
		Renderer::VertexBuffer* vertexBuffer;
		Renderer::IndexBuffer* indexBuffer;
		Renderer::InstanceBuffer* instanceBuffer;
		std::vector<Renderer::GPUBuffer*> buffers;
		Material* material;
		
		void draw(Renderer::RenderContext* context);
	public:
		RenderOperation(
			Renderer::VertexBuffer* vertexBuffer,
			Renderer::IndexBuffer* indexBuffer = 0,
			Renderer::InstanceBuffer* instanceBuffer = 0
		);
		void setMaterial(Material* material);
		void setBuffer(UINT index,Renderer::GPUBuffer* buffer);
		const UINT getBufferCount();
	};
}