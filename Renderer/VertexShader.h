#pragma once
#include"VertexFormat.h"
namespace Renderer
{
	class VertexShader
	{
		friend class Device;
	protected:
		VertexFormat* format;
		VertexShader(VertexFormat* format);
	public:
		VertexFormat* getVertexFormat() const;
	};
}
