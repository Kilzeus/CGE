#include "LightRenderingSystem.h"
#include "EffectLoader.h"

using namespace Scene;
LightRenderingSystem::LightRenderingSystem(Renderer::Device* device, Renderer::RenderContext* context)
	:context(context)
{
	pointLightBuffer = device->createGPUBuffer(sizeof(PointLightBuffer));
	RenderFramework::EffectLoader loader;
	pointLightEffect = loader.loadEffect(device, "lights.fx")->getEffect("point_light");
}


LightRenderingSystem::~LightRenderingSystem()
{
}


void LightRenderingSystem::registerPointLight(const PositionComponent& position, const LightProperties& lightProps)
{
	positions.push_back(position);
	lightProperties.push_back(lightProps);
}


void LightRenderingSystem::update(double deltaTime)
{
	context->setVertexFormat(pointLightEffect->getVertexShader()->getVertexFormat());
	context->setVertexShader(pointLightEffect->getVertexShader());
	context->setFragmentShader(pointLightEffect->getFragmentShader());
	context->setVertexBuffer(boundingVolume);
	context->setGPUBuffer(2, pointLightBuffer);
	context->draw();
}