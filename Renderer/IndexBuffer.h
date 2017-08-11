#pragma once
#include"GPUBuffer.h"
namespace Renderer
{
	enum IndexDataFormat{ Int16, Int32 };
	class IndexBuffer : public GPUBuffer
	{
		//instances created by Device
		friend class Device;
	protected:
		UINT numIndices;
		IndexDataFormat format;
		IndexBuffer(IndexDataFormat format);
	public:
		void setNumIndices(UINT numIndices);
		UINT getNumIndices() const;
		const IndexDataFormat getIndexDataFormat() const;
		virtual void setData(Resource* data,UINT numIndices)=0;
	};
}
