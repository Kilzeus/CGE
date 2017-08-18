#pragma once
#include"Types.h"
#include<glm\glm.hpp>
#include<list>
namespace GUI
{
	class GUIRenderable
	{
		friend class GUIRenderer;
		friend class FontRenderer;
		friend class Font;
		glm::vec4 color;
		glm::vec2 uvTopLeft;
		glm::vec2 uvBottomRight;
		UINT textureID;
		float colormod; // how much result color is affected by color-attribute. max 1.0.
	public:
		GUIRenderable(
			const glm::vec4& color,
			const glm::vec2& uvTopLeft,
			const glm::vec2& uvBottomRight,
			UINT textureID,
			float colormod = 1.f
		);
	};
}