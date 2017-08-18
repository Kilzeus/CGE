#pragma once
#include"Device.h"
#include"RenderContext.h"
#include"GUIElement.h"
#include"GUISkin.h"
#include"SpriteBatch.h"
#include<list>
namespace GUI
{
	/**
		Responsible for rendering visible gui components.
	*/
	class GUIRenderer
	{
		//RenderFramework::SpriteBatch* sprites;
		Renderer::Device* device;
		Renderer::RenderContext* context;
		

		void renderR(RenderFramework::SpriteBatch* sprite, GUIElement* element);
	public:
		GUIRenderer(Renderer::Device* device,Renderer::RenderContext* context);
		void render(Renderer::RenderContext* context, GUIElement* root, GUISkin* skin);
	};
}
