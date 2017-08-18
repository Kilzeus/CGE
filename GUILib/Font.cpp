#include"Font.h"
#include<D3D11.h>
#include<sstream>
#include"GUITextElement.h"
#include"EffectLoader.h"
using namespace GUI;
Font::Font(
	const std::string name,
	Renderer::Texture* texture,
	const std::vector<CharacterInfo> characterInfos,
	const glm::vec2& characterSize,
	UINT baseCharacterOffset,
	std::map<std::pair<char, char>, float>& kerning
	) :name(name), texture(texture), characterInfos(characterInfos),
	characterSize(characterSize), baseCharacterOffset(baseCharacterOffset),
	kerning(kerning)
{
}


Renderer::Texture* Font::getTexture() const
{
	return texture;
}


std::map<std::pair<char, char>, float>& Font::getKerning()
{
	return kerning;
}


float Font::estimateTextLength(const std::string& word)
{
	float length = 0.f;
	for (int i = 0; i < word.size(); i++)
	{
		length += characterInfos[word[i]].bitmapDimensions.x;
	}
	return length;
}

/*
FontVertex* Font::generateVertices(const GUITextElement& element)
{

	FontVertex* vertices = new FontVertex[element.text.size() * 4];
	
	const Renderer::Uint2& textureDimensions = texture->getDimensions();
	int rowPitch = textureDimensions.x / characterSize.x;
	int line = 0;
	float xPosition = 0.0f;
	int index = 0;
	int numElementsOutputted = 0;
	
	float colFactor = characterSize.x / characterSize.x;
	float rowFactor = characterSize.y / characterSize.y;

	glm::vec2 rectTopLeft = element.boundingBox.topLeft;
	glm::vec2 rtSize;
	rtSize.x = element.boundingBox.bottomRight.x - element.boundingBox.topLeft.x;
	rtSize.y = element.boundingBox.bottomRight.y - element.boundingBox.topLeft.y;
	float fontSizeModifier = element.fontSize / rtSize.y;
	
	std::stringstream stream(element.text);
	while(!stream.eof())
	{
		std::string word;
		stream >> word;
		float length = estimateTextLength( word );
		if (element.wrap && xPosition + length >= element.getBoundingBox().bottomRight.x)
		{
			line++;
			xPosition = 0;
		}
		int i = 0;
		while( i < word.size()) 
		{
			if( word[i] == '\n' )
			{
				xPosition = 0;
				line++;
				i++;
				if (element.text[i] == ' ')
					i++;
				continue;
			}
			//calculate uv:s
			int row = ((int)word[i] - this->baseCharacterOffset ) / rowPitch;
			int column = ((int)word[i] - this->baseCharacterOffset ) - ( row * rowPitch );
			float u = (float)column * colFactor;
			float v = (float)row * rowFactor;
			
			//calculate text scroll
			float yPosition = rectTopLeft.y - line * fontSizeModifier;
			float yDifferense = 0.0f;
			if( yPosition > rectTopLeft.y )
			{
				yDifferense = yPosition - rectTopLeft.y;
				if (yDifferense > this->characterSize.y) continue;	//if the line isnt visible jump over it
			}
			//top left
			vertices[index].position.x = rectTopLeft.x + xPosition;
			vertices[index].position.y = yPosition - yDifferense;
			vertices[index].uv.x = u;
			vertices[index].uv.y = v + yDifferense * 2.0f;
			vertices[index].color = element.renderable->color;
			index++;
			//top right
			vertices[index].position.x = rectTopLeft.x + xPosition + fontSizeModifier;
			vertices[index].position.y = yPosition - yDifferense;
			vertices[index].uv.x = u + colFactor;
			vertices[index].uv.y = v + yDifferense * 2.0f;
			vertices[index].color = element.renderable->color;
			index++;
			//bottom left
			vertices[index].position.x = rectTopLeft.x + xPosition;
			vertices[index].position.y = yPosition - fontSizeModifier;
			vertices[index].uv.x = u;
			vertices[index].uv.y = v + rowFactor;
			vertices[index].color = element.renderable->color;
			index++;
			//bottom right
			vertices[index].position.x = rectTopLeft.x + xPosition + fontSizeModifier;
			vertices[index].position.y = yPosition - fontSizeModifier;
			vertices[index].uv.x = u + colFactor;
			vertices[index].uv.y = v + rowFactor;
			vertices[index].color = element.renderable->color;
			index++;
			xPosition += this->characterWidths[word[i]] / rtSize.x * 2.0f;
			i++;
			if(element.wrap && xPosition >= element.boundingBox.bottomRight.x )
			{
				line++;
				xPosition = 0;
			}
		}
		xPosition +=  fontSizeModifier;
		numElementsOutputted += i;
	}	
	float textHeight = line * fontSizeModifier;
	UINT numVertices = numElementsOutputted;
	return vertices;
	
}*/