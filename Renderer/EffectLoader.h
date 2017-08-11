#pragma once
#include"EffectGroup.h"
#include"Device.h"
#include"Logger.h"
namespace RenderFramework
{
	class EffectLoader
	{
	public:
		EffectGroup* loadEffect(
			Renderer::Device* device,std::string filename
		);
	};
}