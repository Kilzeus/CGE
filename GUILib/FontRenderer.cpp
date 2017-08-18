#include "FontRenderer.h"
#include"Material.h"
#include"EffectLoader.h"
#include"GUITextElement.h"
#include<sstream>

using namespace GUI;
FontRenderer::FontRenderer(Renderer::Device* device, 
	const std::string effectFile, const std::string effectName,
	Font* font) :font(font)
{
	RenderFramework::Material* material = new RenderFramework::Material;
	RenderFramework::EffectLoader importer;
	RenderFramework::EffectGroup* effectGroup = importer.loadEffect(device, effectFile);
	RenderFramework::RenderEffect* effect = effectGroup->getEffect(effectName);
	material->setRenderEffect(effect);
	material->setTexture(0, font->texture);
	screenTopLeft = glm::vec2(device->getScreenSpaceTopLeft().x, device->getScreenSpaceTopLeft().y);
	sprites = new RenderFramework::SpriteBatch(
		device, material
		);
}


FontRenderer::~FontRenderer()
{
}


void FontRenderer::render(Renderer::RenderContext* context, const GUITextElement* root)
{
	sprites->begin();
	generate(*root);
	for each (GUITextElement* child in root->children)
	{
		renderR(context, child);
	}
	sprites->end(context);
}


void FontRenderer::renderR(Renderer::RenderContext* context, const GUITextElement* element)
{
	generate(*element);
	for each (GUITextElement* child in element->children)
	{
		renderR(context, child);
	}
}

/*
	Generates positions and uvs for text. Feed coordinates where top left is {0,0} and bottom right is {1,1},
	method handles the transformations to renderer coordinates.
*/
void FontRenderer::generate(const GUITextElement& element)
{

	const Renderer::Uint2& textureDimensions = font->texture->getDimensions();
	int rowPitch = textureDimensions.x / font->characterSize.x;
	int line = 0;
	float xPosition = 0.0f;
	int index = 0;

	float colFactor = font->characterSize.x / textureDimensions.x;
	float rowFactor = font->characterSize.y / textureDimensions.y;

	glm::vec2 rectTopLeft = element.boundingBox.topLeft*2.f; //(element.boundingBox.topLeft + screenTopLeft) * 2.f;
	glm::vec2 bottomRight = element.boundingBox.bottomRight*2.f; //(element.boundingBox.bottomRight + screenTopLeft) * 2.f;
	// do size calculations when bottomright>recttop.
	glm::vec2 rtSize;
	rtSize.x = bottomRight.x - rectTopLeft.x;
	rtSize.y = bottomRight.y - rectTopLeft.y;
	rectTopLeft.x += screenTopLeft.x;
	rectTopLeft.y = -(rectTopLeft.y - screenTopLeft.y);
	bottomRight.x += screenTopLeft.x;
	bottomRight.y = -(bottomRight.y - screenTopLeft.y);
	float fontSizeModifier = element.fontSize * rtSize.y;
	std::map<std::pair<char, char>, float>& kerning = font->getKerning();

	std::stringstream stream(element.text);
	while (!stream.eof())
	{
		std::string word;
		stream >> word;
		float length = font->estimateTextLength(word);
		if (element.wrap && xPosition + length >= bottomRight.x)
		{
			line++;
			xPosition = 0;
		}
		int i = 0;
		while (i < word.size())
		{
			if (word[i] == '\n')
			{
				xPosition = 0;
				line++;
				i++;
				if (element.text[i] == ' ')
				{
					i++;
					continue;
				}
			}
			//calculate uv:s
			int row = ((int)word[i] - font->baseCharacterOffset) / rowPitch;
			int column = ((int)word[i] - font->baseCharacterOffset) - (row * rowPitch);
			float u = (float)column * colFactor;
			float v = (float)row * rowFactor;

			//calculate text scroll
			float yPosition = rectTopLeft.y - line * fontSizeModifier;
			float yDifferense = 0.0f;
			if (yPosition > rectTopLeft.y)
			{
				yDifferense = yPosition - rectTopLeft.y;
				if (yDifferense > font->characterSize.y) continue;	//if the line isnt visible jump over it
			}
			glm::vec2 position;
			float y = font->characterInfos[word[i]].bitmapDimensions.y / font->characterSize.y;
			float x = font->characterInfos[word[i]].bitmapDimensions.x / font->characterSize.x;
			glm::vec2 size(x*fontSizeModifier, y * -fontSizeModifier);

			RenderFramework::SpriteRect rect(glm::vec2(u, v), glm::vec2(u + colFactor*x, v + rowFactor*y));

			//bearings
			float bearingX = font->characterInfos[word[i]].bearings.x * x * fontSizeModifier;
			position.y = yPosition - yDifferense;
			float bearingY = font->characterInfos[word[i]].bearings.y;
			bearingY *= y * -fontSizeModifier;
			position.y -= bearingY;

			position.x = rectTopLeft.x + xPosition + bearingX;
			sprites->draw(position, size, element.renderable->color, glm::vec2(0.f, 0.f), rect,0.f);
			
			if (element.wrap && xPosition >= bottomRight.x)
			{
				line++;
				xPosition = 0;
			}
			/*std::map<std::pair<char, char>, float>::iterator iter = kerning.find(std::pair<char, char>(word[i], word[i + 1]));
			if (iter != kerning.end())
			{
				xPosition += font->characterInfos[word[i]].advance * x * fontSizeModifier + iter->second;
			}
			else*/ 
			float adv = font->characterInfos[word[i]].advance;
			xPosition += adv * x * fontSizeModifier;
			i++;
		}
	}
}