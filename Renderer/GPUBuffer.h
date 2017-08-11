#pragma once
#include"Types.h"
#include"Resource.h"
namespace Renderer
{
	class GPUBuffer
	{
	protected:
		GPUBuffer() {};
		UINT size;
	public:
		virtual void setData(Resource* data)=0;
		const UINT getSize() const;
	};
}
