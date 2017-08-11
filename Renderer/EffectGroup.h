#pragma once
#include"RenderEffect.h"
#include<map>
namespace RenderFramework
{
	class EffectGroup
	{
		std::string name;
		std::map<std::string,RenderEffect*> effects;
	public:
		EffectGroup(std::string name);
		void addEffect(std::string name,RenderEffect* effect);
		RenderEffect* getEffect(const std::string name);
	};
}