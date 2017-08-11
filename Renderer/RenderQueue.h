#pragma once
#include"RenderState.h"
#include"RenderOperation.h"
#include<map>
#include<list>
namespace RenderFramework
{
	class RenderQueue
	{
		std::map<RenderState*,std::list<RenderOperation*>> operations;
	public:
		RenderQueue();
		void addRenderState(RenderState* state);
		void addRenderOperation(
			RenderState* state,RenderOperation* operation
		);
		void draw(Renderer::RenderContext* context);
	};
}