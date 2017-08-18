#pragma once
#include"Texture.h"
#include"RenderContext.h"
#include<glm\glm.hpp>
#include<map>
namespace GUI
{
	struct FontVertex
	{
		glm::vec2 position;
		glm::vec2 uv;
		glm::vec4 color;
	};

	struct CharacterInfo
	{
		float advance;
		glm::vec2 bitmapDimensions;
		glm::vec2 bearings;

	};
	/**
		Represents a font. Contains all the data required to render
		text using this font. 
	*/
	class Font
	{
		friend class FontRenderer;
		const std::vector<CharacterInfo> characterInfos;
		bool bold;
		bool italic;
		UINT baseCharacterOffset;
		std::string name;
		glm::vec2 characterSize;
		Renderer::Texture* texture;
		std::map<std::pair<char, char>, float> kerning;

		float estimateTextLength(const std::string& word);
	//	FontVertex* generateVertices(const class GUITextElement& element);
	public:
		Font(
			const std::string name,
			Renderer::Texture* texture,
			const std::vector<CharacterInfo> characterInfos,
			const glm::vec2& characterSize,
			UINT baseCharacterOffset,
			std::map<std::pair<char, char>, float>& kerning
		);
		Renderer::Texture* getTexture() const;
		std::map<std::pair<char, char>, float>& getKerning();
	};
}