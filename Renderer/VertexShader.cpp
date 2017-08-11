#include"VertexShader.h"

using namespace Renderer;
VertexShader::VertexShader(VertexFormat* format)
:format(format)
{
}


VertexFormat* VertexShader::getVertexFormat() const
{
	return format;
}