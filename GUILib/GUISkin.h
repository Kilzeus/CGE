#pragma once
#include"GUIRenderable.h"
#include"Font.h"
#include"SpriteBatch.h"
#include<unordered_map>
#include<string>
namespace GUI
{
	/*
		Contains GUI Renderables and manages a visual representations
		rendering information.
	*/
	class GUISkin
	{
		friend class GUIRenderer;
		std::unordered_map<std::string,GUIRenderable> renderInfos;
		RenderFramework::SpriteBatch* sprites;
		Font* font;

		void renderBegin();
		void renderEnd(Renderer::RenderContext* context);
		RenderFramework::SpriteBatch* getSprite() const;
	public:
		GUISkin(Renderer::Device* device, Font* font, const std::string effectFile,
			const std::string effectName, std::list<std::string>& textures);
		GUISkin(Renderer::Device* device, Font* font, const std::string effectFile,
			const std::string effectName, Renderer::Texture* textures,UINT numTextures);
		void add(const std::string id,const GUIRenderable& renderInfo);
		GUIRenderable* get(const std::string id);
		void setFont(const Font* font);
	};
}