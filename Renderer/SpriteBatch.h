#pragma once
#include"RenderContext.h"
#include"Material.h"
#include"Device.h"
#include<glm\glm.hpp>
#include"Sprite.h"
namespace RenderFramework
{

	struct SpriteRect
	{
		glm::vec2 topLeft;
		glm::vec2 bottomRight;
		SpriteRect(
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight
		):topLeft(topLeft),bottomRight(bottomRight){}
	};

	/**
		A collection of sprites batched together
		for efficient rendering. Sprites are meant
		to always face the camera.
	*/
	class SpriteBatch
	{
		std::vector<Renderer::VertexBuffer*> vertexBuffers;
		std::vector<SpriteVertex*> batchingBuffers;
		std::vector<UINT> bufferSizes;
		UINT buffersUsed;
		RenderFramework::Material* material;
		Renderer::Device* device; // keep pointer to generate new vertex buffers as required.
	public:
		SpriteBatch(
			Renderer::Device* device,
			RenderFramework::Material* material
		);
		void begin();
		void draw(
			const glm::vec2& position,	//topleft
			const glm::vec2& size,
			const glm::vec4& color,
			const glm::vec2& origin = glm::vec2(0.f,0.f),	//relative to topleft
			const SpriteRect& rect = SpriteRect(glm::vec2(0.f,0.f),glm::vec2(1.f,1.f)),
			float colormod = 1.f
		);
		void end(Renderer::RenderContext* context);

		static UINT bufferSize;	//public so can be changed to match graphics capabilities
	};
}