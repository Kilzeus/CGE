#pragma once
#include"Device.h"
#include<glm\glm.hpp>
namespace Scene
{
	struct DirectionalLightBuffer
	{
		glm::vec3 direction;
		float intensity;
		glm::vec3 color;
		float ambientIntensity;
	};


	class DirectionalLight
	{
		DirectionalLightBuffer directionalLightBuffer;
		Renderer::GPUBuffer* gpubuffer;
	public:
		DirectionalLight(Renderer::Device* device, const glm::vec3& lightDirection, 
			float lightIntensity, const glm::vec3& lightColor, float ambientIntensity);
		~DirectionalLight();
		void onRender(Renderer::RenderContext* context);
	};
}
