#include "GUIRenderer.h"
#include"TextureLoader.h"
#include"EffectLoader.h"

using namespace GUI;
GUIRenderer::GUIRenderer(
	Renderer::Device* device,Renderer::RenderContext* context
	) :device(device), context(context)
{
/*	RenderFramework::Material* material = new RenderFramework::Material;
	RenderFramework::EffectLoader importer;
	RenderFramework::EffectGroup* effectGroup = importer.loadEffect(device,"test.fx");
	RenderFramework::RenderEffect* effect = effectGroup->getEffect(std::string("basicEffect"));
	material->setRenderEffect(effect);
	AssetSystem::TextureLoader* loader = new AssetSystem::TextureLoader(device);
	Renderer::Texture* texture = loader->loadTexture("button2.png");
	material->setTexture(0,texture);
	sprites = new RenderFramework::SpriteBatch(
		device,material
	);*/
}


void GUIRenderer::renderR(RenderFramework::SpriteBatch* sprite, GUIElement* element)
{
	RenderFramework::SpriteRect rect(
		element->renderable->uvTopLeft,element->renderable->uvBottomRight
	);
	sprite->draw(
		element->getBoundingBox().topLeft,
		element->getBoundingBox().bottomRight,
		element->renderable->color,
		glm::vec2(0.f,0.f),
		rect,
		element->renderable->colormod
	);
	std::list<GUIElement*>::iterator iter = element->children.begin();
	while(iter != element->children.end())
	{
		renderR(sprite, *iter);
		iter++;
	}
}


void GUIRenderer::render(Renderer::RenderContext* context, GUIElement* root, GUISkin* skin)
{
	RenderFramework::SpriteBatch* sprite = skin->getSprite();
	sprite->begin();
	RenderFramework::SpriteRect rect(
		root->renderable->uvTopLeft,root->renderable->uvBottomRight
	);
	sprite->draw(
		root->getBoundingBox().topLeft,
		root->getBoundingBox().bottomRight,
		root->renderable->color,
		glm::vec2(0.f,0.f),
		rect,
		root->renderable->colormod
	);
	std::list<GUIElement*>::iterator iter = root->children.begin();
	while(iter != root->children.end())
	{
		renderR(sprite, *iter);
		iter++;
	}
	sprite->end(context);
}