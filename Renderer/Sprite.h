#pragma once
#include<glm\glm.hpp>
#include"Material.h"
#include<vector>
namespace RenderFramework
{
	struct SpriteVertex
	{
		glm::vec2 position;
		glm::vec2 uv;
		glm::vec4 color;
		float colormod;
	};

	class Sprite
	{
		glm::vec2 position;
		glm::vec2 size;
		Renderer::VertexBuffer* vbuffer;
		Material* material;
	public:
		Sprite(
			Renderer::Device* device,
			const glm::vec2& position,
			const glm::vec2& size,
			const glm::vec4& color,
			Material* material,
			float colormod = 1.f
		);
		void render(Renderer::RenderContext* context);
		void setMaterial(Material* material);
	};
}