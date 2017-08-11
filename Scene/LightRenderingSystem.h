#pragma once
#include"GPUBuffer.h"
#include"Device.h"
#include"Component.h"
#include"EffectGroup.h"
#include"PositionComponent.h"
#include"LightProperties.h"
#include<vector>
namespace Scene
{

	class LightRenderingSystem
	{
		struct PointLightBuffer
		{
			float intensity;
			glm::vec3 color;
		};

		struct DirectionalLightBuffer
		{
			glm::vec3 direction;
			float intensity;
			glm::vec3 color;
			float ambientIntensity;
		};

		Renderer::GPUBuffer* pointLightBuffer;
		//Renderer::GPUBuffer* directionalLightBuffer;
		Renderer::VertexBuffer* boundingVolume;
		RenderFramework::RenderEffect* pointLightEffect;

		std::vector<PositionComponent> positions;
		std::vector<LightProperties> lightProperties;
		Renderer::RenderContext* context;
	public:
		LightRenderingSystem(Renderer::Device* device, Renderer::RenderContext* context);
		~LightRenderingSystem();
		void registerPointLight(const PositionComponent& position, const LightProperties& lightProps);
		void update(double deltaTime);
	};
}


