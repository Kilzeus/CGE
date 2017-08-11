#pragma once
#include"Core.h"
#include"RenderContext.h"
#include"RenderTargetView.h"
#include"Sprite.h"
#include"GPUBuffer.h"
#include<vector>
#include<glm\glm.hpp>
namespace RenderFramework
{
	/*
		Implements deferred rendering and lightning. Useful if you have 
		a complex scene where there are a lot of lights.

		1st pass uses 3 rendertargets, in order:
		1. color - R16G16B16A16_unorm.
		2. normals - R16G16B16A16_float.
		3. depth - R32B32_float.
		2nd pass renders lights to 1 rendertarget.
		3rd pass combines the results to backbuffer.

	*/
	class DeferredRenderer
	{
		Renderer::RenderContext* context;
		Renderer::RenderTargetView** gbufferTargets;
		Renderer::RenderTargetView* lightMap;
		UINT numRenderTargets;
		Sprite* drawTarget;
		Material* lightmapMaterial; // holds gbuffer textures for input
		Material* combineMaterial;
	public:
		DeferredRenderer(Renderer::Device* device, Renderer::DeviceProperties& properties);
		~DeferredRenderer();
		void begin();
		void lightPass();
		void renderDirectionalLight();
		void present();
	};
}

