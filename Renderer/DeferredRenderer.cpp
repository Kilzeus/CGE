#include "DeferredRenderer.h"
#include"EffectLoader.h"


using namespace RenderFramework;
DeferredRenderer::DeferredRenderer(Renderer::Device* device, Renderer::DeviceProperties& properties)
{
	context = device->getRenderContext();
	lightmapMaterial = new RenderFramework::Material;
	combineMaterial = new RenderFramework::Material;

	//color render target
	numRenderTargets = 3;
	UINT index = 0;
	gbufferTargets = new Renderer::RenderTargetView*[numRenderTargets];
	Renderer::Texture* texture = device->createTexture(
		0, properties.resolution, Renderer::TextureFormat::R16G16B16A16_unorm, 1, false, true);
	Renderer::RenderTargetView* renderTarget = device->createRenderTarget(texture);
	gbufferTargets[index] = renderTarget;
	lightmapMaterial->setTexture(index, texture);
	combineMaterial->setTexture(index, texture);
	index++;

	//normal render target
	texture = device->createTexture(
		0, properties.resolution, Renderer::TextureFormat::R16G16B16A16_float, 1, false, true);
	renderTarget = device->createRenderTarget(texture);
	gbufferTargets[index] = renderTarget;
	lightmapMaterial->setTexture(index, texture);
	combineMaterial->setTexture(index, texture);
	index++;

	//depth rendertarget
	texture = device->createTexture(
		0, properties.resolution, Renderer::TextureFormat::R32G32_float, 1, false, true);
	renderTarget = device->createRenderTarget(texture);
	gbufferTargets[index] = renderTarget;
	lightmapMaterial->setTexture(index, texture);
	combineMaterial->setTexture(index, texture);
	index++;

	//light map, not part of gbuffer
	texture = device->createTexture(
		0, properties.resolution, Renderer::TextureFormat::R16G16B16A16_float, 1, false, true);
	renderTarget = device->createRenderTarget(texture);
	combineMaterial->setTexture(index, texture);
	lightMap = renderTarget;

	RenderFramework::EffectLoader loader;
	RenderFramework::EffectGroup* eg = loader.loadEffect(device, "composer.fx");
	combineMaterial->setRenderEffect(eg->getEffect("composer"));
	lightmapMaterial->setRenderEffect(eg->getEffect("directional_light"));
	
	drawTarget = new Sprite(device, glm::vec2(-1.f, 1.f), glm::vec2(2.f, -2.f), glm::vec4(1.f, 1.f, 1.f, 1.f), lightmapMaterial);

	std::vector<float*> colors;
	float* color = new float[4] { 0.f, 0.f, 0.f, 0.f };
	colors.push_back(color);
	float* ncolor = new float[4] { 0.5f, 0.5f, 0.5f, 0.0f };
	colors.push_back(ncolor);
	float* dcolor = new float[2] { 1.f, 1.f};
	colors.push_back(dcolor);
	colors.push_back(color);
	context->setRenderTargetClearColors(colors);
}


DeferredRenderer::~DeferredRenderer()
{
	delete combineMaterial;
	delete lightmapMaterial;
	delete drawTarget;
	delete lightMap;
	delete[] gbufferTargets;
}


/*
	Call this before you start deferred rendering pass.
*/
void DeferredRenderer::begin()
{
	context->setAlphaBlendingState(Renderer::AlphaBlendDisabled);
	context->setRenderTargets(gbufferTargets, numRenderTargets);
	context->renderBegin();
}


/*
	Sets lightmap as rendertarget. Render only lights after this.
*/
void DeferredRenderer::lightPass()
{
	context->enableDepthTesting(false);
	context->unbindRenderTargets();
	context->setRenderTarget(lightMap);
	context->renderBegin(false);
	drawTarget->setMaterial(lightmapMaterial);
}


void DeferredRenderer::renderDirectionalLight()
{	
	drawTarget->render(context);
}


/*
	End deferred rendering. Will combine GBuffer and lightmap to backbuffer.
*/
void DeferredRenderer::present()
{
	context->enableDepthTesting(false);
	context->unbindRenderTargets();
	context->setBackbufferRenderTarget();
	/*for (int i = 0; i < 4; i++)
		context->generateMipmaps(combineMaterial->getTexture(i));*/
	drawTarget->setMaterial(combineMaterial);
	drawTarget->render(context);
}