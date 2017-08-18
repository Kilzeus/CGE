#pragma once
#include<glm\glm.hpp>
#include<list>
#include"GUIElementController.h"
#include"GUIEvent.h"
#include"GUIRenderable.h"
#include"BoundingBox.h"
#include"GUISkin.h"
namespace GUI
{
	/**
		A gui element that contains a pointer to visual 
		representation and some attributes like position.
	*/
	class GUIElement
	{
	protected:
		friend class GUICore;
		friend class GUIRenderer;
		BoundingBox boundingBox;
		GUIElementController* controller;
		GUIRenderable* renderable;
		GUIElement* parent;
		std::list<GUIElement*> children;
		bool disabled;
		bool visible;
		std::string id;
		bool changed;

		GUIElement(
			const std::string id,
			const glm::vec2& topLeft,
			const glm::vec2& bottomRight
		);
		void setSkinRecursive(GUISkin* skin);
	public:
		void setBoundingBox(const BoundingBox& box);
		const BoundingBox& getBoundingBox() const;
		void addChild(GUIElement* element);
		void setController(GUIElementController* controller);
		void handleEvent(GUIEvent& evt);
		const std::string& getID() const;
	};
}