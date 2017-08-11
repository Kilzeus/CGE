#pragma once
#include"VertexShader.h"
#include"FragmentShader.h"
#include"GeometryShader.h"
#include<string>
namespace RenderFramework
{
	class RenderEffect
	{
		std::string name;
		Renderer::VertexShader* vertexShader;
		Renderer::FragmentShader* fragmentShader;
		Renderer::GeometryShader* geometryShader;
	public:
		RenderEffect(
			std::string name,
			Renderer::VertexShader* vertexShader,
			Renderer::FragmentShader* fragmentShader,
			Renderer::GeometryShader* geometryShader = 0
		);
		Renderer::VertexShader* getVertexShader() const;
		Renderer::FragmentShader* getFragmentShader() const;
		Renderer::GeometryShader* getGeometryShader() const;
	};
}