#pragma once
#include"RenderContext.h"
namespace RenderFramework
{
	struct RenderState
	{
		bool cullBackfaces;
		bool depthTesting;
		Renderer::PrimitiveTopology topology;
		Renderer::AlphaBlendingState alphaState;
	};
}
