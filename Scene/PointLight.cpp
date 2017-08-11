#include "PointLight.h"
#include"EffectLoader.h"


using namespace Scene;
PointLight::PointLight(Renderer::Device* device,
	Renderer::VertexBuffer* boundingVolume,
	float intensity, const glm::vec3& color)
	:boundingVolume(boundingVolume)
{
	lightBuffer.color = color;
	lightBuffer.intensity = intensity;
	gpubuffer = device->createGPUBuffer(sizeof(PointLightBuffer));
	gpubuffer->setData(&Resource(sizeof(PointLightBuffer), &lightBuffer));
	type = Scene::ComponentType::Light;
	RenderFramework::EffectLoader loader;
	effect = loader.loadEffect(device,"lights.fx")->getEffect("point_light");
}


PointLight::~PointLight()
{
	delete gpubuffer;
}


void PointLight::onUpdate(double timeDelta)
{

}


void PointLight::onRender(Renderer::RenderContext* context)
{
	context->setVertexFormat(effect->getVertexShader()->getVertexFormat());
	context->setVertexShader(effect->getVertexShader());
	context->setFragmentShader(effect->getFragmentShader());
	context->setVertexBuffer(boundingVolume);
	context->setGPUBuffer(2, gpubuffer);
	context->draw();
}