#pragma once
#include"PositionComponent.h"
#include<vector>
#include<atomic>
namespace Scene
{
	template<class Component>
	class ComponentStorage
	{
		std::vector<Component> readBuffer;
		std::vector<int> buffer1IDs;
		std::vector<Component> writeBuffer;
		std::vector<int> buffer2IDs;
		std::atomic<int> index;
	public:
		ComponentStorage()
		{

		}

		const std::vector<Component>& getReadBuffer()
		{
			int buffer = index.load();
		}
	};
}
