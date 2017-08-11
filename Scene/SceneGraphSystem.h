#pragma once
#include"PositionComponent.h"
#include<vector>
namespace Scene
{
	class SceneGraphSystem
	{
		std::vector<PositionComponent> positions;
	public:
		SceneGraphSystem();
		~SceneGraphSystem();
	};
}
