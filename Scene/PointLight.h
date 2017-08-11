#pragma once
#include"GPUBuffer.h"
#include"Device.h"
#include"Component.h"
#include"EffectGroup.h"
#include<glm\glm.hpp>
namespace Scene
{
	struct PointLightBuffer
	{
		float intensity;
		glm::vec3 color;
	/*	glm::vec3 position;
		float padding;*/
	};


	class PointLight : public Component
	{
		PointLightBuffer lightBuffer;
		Renderer::GPUBuffer* gpubuffer;
		Renderer::VertexBuffer* boundingVolume;
		RenderFramework::RenderEffect* effect;
	public:
		PointLight(Renderer::Device* device, Renderer::VertexBuffer* boundingVolume, 
			float intensity,const glm::vec3& color);
		~PointLight();
		void onRender(Renderer::RenderContext* context);
		void onUpdate(double timeDelta);
	};
}

