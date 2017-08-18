#pragma once
#include"VertexBuffer.h"
#include"Material.h"
#include<glm\glm.hpp>
namespace AssetSystem
{
	struct MeshVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;
		glm::vec2 uv;
	};


	class MeshPart
	{
		friend class MeshLoader;
		Renderer::VertexBuffer* vertexBuffer;
		RenderFramework::Material* material;
	public:
		MeshPart();
		~MeshPart();
		Renderer::VertexBuffer* getVertexbuffer();
		void onRender(Renderer::RenderContext* context);
		void onUpdate(double timeDelta);
	};
}

