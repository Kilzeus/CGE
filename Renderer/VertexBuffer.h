#pragma once
#include "GPUBuffer.h"
namespace Renderer
{
	/**
		A buffer for holding vertex data.
	*/
	class VertexBuffer : public GPUBuffer
	{
	protected:
		UINT numVertices;
		UINT vertexByteSize;
		VertexBuffer() {};
		bool dynamic;
	public:
		void setNumVertices(UINT numVertices);
		void setVertexByteSize(UINT size);
		const UINT getNumVertices() const;
		UINT getVertexByteSize() const;
		virtual void setData(
			Resource* data,UINT numVertices,UINT vertexByteSize
		)=0;
	};
}
