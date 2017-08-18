#include"GUIRenderable.h"

using namespace GUI;
GUIRenderable::GUIRenderable(
	const glm::vec4& color,
	const glm::vec2& uvTopLeft,
	const glm::vec2& uvBottomRight,
	UINT textureID,
	float colormod
):color(color),uvTopLeft(uvTopLeft),
uvBottomRight(uvBottomRight), textureID(textureID), colormod(colormod)
{

}