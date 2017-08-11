#include"RenderQueue.h"

using namespace RenderFramework;
RenderQueue::RenderQueue()
{
}


void RenderQueue::addRenderState(RenderState* state)
{
	operations.insert(std::make_pair(state,std::list<RenderOperation*>()));
}


void RenderQueue::addRenderOperation(
	RenderState* state,RenderOperation* operation
)
{
	operations[state].push_back(operation);
}


void RenderQueue::draw(Renderer::RenderContext* context)
{
	std::map<RenderState*,std::list<RenderOperation*>>::iterator iter = operations.begin();
	while(iter != operations.end())
	{
		//set rendering states
		RenderState* state = iter->first;
		context->setAlphaBlendingState(state->alphaState);
		context->enableDepthTesting(state->depthTesting);
		context->enableBackfaceCulling(state->cullBackfaces);
		context->setPrimitiveTopology(state->topology);
		//render for current state
		std::list<RenderOperation*>::iterator iRenderOp = iter->second.begin();
		while(iRenderOp != iter->second.end())
		{
			(*iRenderOp)->draw(context);
			iRenderOp++;
		}
		iter++;
	}
}