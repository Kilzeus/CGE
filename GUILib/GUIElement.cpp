#include"GUIElement.h"

using namespace GUI;
GUIElement::GUIElement(
	const std::string id,
	const glm::vec2& topLeft,
	const glm::vec2& bottomRight
	) :id(id), boundingBox(topLeft, bottomRight), changed(false)
{
}


void GUIElement::handleEvent(GUIEvent& evt)
{
	if(!disabled)
	{
		std::list<GUIElement*>::iterator iter = children.begin();
		while(iter != children.end())
		{
			(*iter)->handleEvent(evt);
			iter++;
		}
		if(evt.position.x >= boundingBox.topLeft.x && evt.position.y >= boundingBox.topLeft.y &&
			evt.position.x <= boundingBox.bottomRight.x && evt.position.y >= boundingBox.bottomRight.y)
		{
			if(controller->handleEvent(evt,*this)) evt.processed = true;
		}
	}
}


void GUIElement::setSkinRecursive(GUISkin* skin)
{
	renderable = skin->get(id);
	std::list<GUIElement*>::iterator iter = children.begin();
	while(iter != children.end())
	{
		(*iter)->setSkinRecursive(skin);
		iter++;
	}
}


const std::string& GUIElement::getID() const
{
	return id;
}

void GUIElement::setBoundingBox(const BoundingBox& box)
{
	boundingBox = box;
}

const BoundingBox& GUIElement::getBoundingBox() const
{
	return boundingBox;
}

void GUIElement::addChild(GUIElement* element)
{
	children.push_back(element);
	element->parent = this;
	GUIElement* pr = this;
	while (pr->parent != 0)
	{
		pr->changed = true;
		pr = pr->parent;
	}
}