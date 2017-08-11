#include "DirectionalLight.h"


using namespace Scene;
DirectionalLight::DirectionalLight(Renderer::Device* device, const glm::vec3& direction,
	float intensity, const glm::vec3& color, float ambientIntensity)
{
	directionalLightBuffer.direction = direction;
	directionalLightBuffer.intensity = intensity;
	directionalLightBuffer.color = color;
	directionalLightBuffer.ambientIntensity = ambientIntensity;
	gpubuffer = device->createGPUBuffer(sizeof(DirectionalLightBuffer));
	gpubuffer->setData(&Resource(sizeof(DirectionalLightBuffer), &directionalLightBuffer));
}


DirectionalLight::~DirectionalLight()
{
	delete gpubuffer;
}


void DirectionalLight::onRender(Renderer::RenderContext* context)
{
	context->setGPUBuffer(1, gpubuffer);
}