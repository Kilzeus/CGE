#pragma once
#include "gpubuffer.h"
namespace Renderer
{
	class InstanceBuffer : public GPUBuffer
	{
		int numElements;
	public:
		void setInstanceCount(int numElements);
	};
}
