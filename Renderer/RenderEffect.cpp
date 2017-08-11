#include"RenderEffect.h"

using namespace RenderFramework;
RenderEffect::RenderEffect(
	std::string name,
	Renderer::VertexShader* vertexShader,
	Renderer::FragmentShader* fragmentShader,
	Renderer::GeometryShader* geometryShader
):name(name),vertexShader(vertexShader),
fragmentShader(fragmentShader),geometryShader(geometryShader)
{
}


Renderer::VertexShader* RenderEffect::getVertexShader() const
{
	return vertexShader;
}


Renderer::FragmentShader* RenderEffect::getFragmentShader() const
{
	return fragmentShader;
}


Renderer::GeometryShader* RenderEffect::getGeometryShader() const
{
	return geometryShader;
}