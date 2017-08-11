#include"EffectGroup.h"

using namespace RenderFramework;
EffectGroup::EffectGroup(std::string name)
:name(name)
{
}


void EffectGroup::addEffect(
	std::string name,RenderEffect* effect
)
{
	effects.insert(std::make_pair(name,effect));
}


RenderEffect* EffectGroup::getEffect(const std::string name)
{
	std::map<std::string,RenderEffect*>::iterator iter =
		effects.find(name);
	if(iter != effects.end()) return iter->second;
	else return 0;
}