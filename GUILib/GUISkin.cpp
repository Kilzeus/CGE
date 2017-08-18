#include"GUISkin.h"
#include"EffectLoader.h"
#include"TextureLoader.h"

using namespace GUI;
GUISkin::GUISkin(Renderer::Device* device, Font* font, const std::string effectFile,
	const std::string effectName, std::list<std::string>& textures) 
	:font(font)
{
	RenderFramework::Material* material = new RenderFramework::Material;
	RenderFramework::EffectLoader importer;
	RenderFramework::EffectGroup* effectGroup = importer.loadEffect(device, effectFile);
	RenderFramework::RenderEffect* effect = effectGroup->getEffect(effectName);
	material->setRenderEffect(effect);
	AssetSystem::TextureLoader* loader = new AssetSystem::TextureLoader(device);
	std::list<std::string>::iterator iter = textures.begin();
	int i = 0;
	while (iter != textures.end()) {
		Renderer::Texture* texture = loader->loadTexture(*iter);
		material->setTexture(i, texture);
		iter++;
		i++;
	}
	//material->setTexture(0, font->getTexture());
	sprites = new RenderFramework::SpriteBatch(
		device, material
	);
}


GUISkin::GUISkin(Renderer::Device* device, Font* font, const std::string effectFile,
	const std::string effectName, Renderer::Texture* textures, UINT numTextures) 
	:font(font)
{
	RenderFramework::Material* material = new RenderFramework::Material;
	RenderFramework::EffectLoader importer;
	RenderFramework::EffectGroup* effectGroup = importer.loadEffect(device, effectFile);
	RenderFramework::RenderEffect* effect = effectGroup->getEffect(effectName);
	material->setRenderEffect(effect);
	int i = 0;
	while (i<numTextures) {
		material->setTexture(i, &textures[i]);
		i++;
	}
	//material->setTexture(0, font->getTexture());
	sprites = new RenderFramework::SpriteBatch(
		device, material
		);
}


void GUISkin::add(const std::string id,const GUI::GUIRenderable& renderInfo)
{
	renderInfos.insert(std::make_pair(id,renderInfo));
}


GUIRenderable* GUISkin::get(const std::string id)
{

	std::unordered_map<std::string,GUI::GUIRenderable>::iterator iter = renderInfos.find(id);
	if(iter != renderInfos.end()) return &iter->second;
	else return 0;
}


void GUISkin::renderBegin()
{
	sprites->begin();
}


void GUISkin::renderEnd(Renderer::RenderContext* context)
{
	sprites->end(context);
}


RenderFramework::SpriteBatch* GUISkin::getSprite() const
{
	return sprites;
}