#pragma once
#include"RenderContext.h"
namespace Scene
{
	enum ComponentType{Geometry, Light, Other};

	/*
		A visual component that can be associated with a node for rendering.
	*/
	class Component
	{
	protected:
		ComponentType type;
	public:
		virtual void onRender(class Renderer::RenderContext* context) = 0;
		virtual void onUpdate(double timeDelta) = 0;
		ComponentType getType() { return type; };
	};
}
