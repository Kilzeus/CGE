#pragma once
#include"SpriteBatch.h"
#include"Font.h"
namespace GUI
{
	class FontRenderer
	{
		RenderFramework::SpriteBatch* sprites;
		Font* font;
		glm::vec2 screenTopLeft;

		void generate(const class GUITextElement& element);
		void renderR(Renderer::RenderContext* context, const GUITextElement* element);
	public:
		FontRenderer(Renderer::Device* device,
			const std::string effectFile,
			const std::string effectName,
			Font* font);
		~FontRenderer();
		void render(Renderer::RenderContext* context, const GUITextElement* root);
	};
}

