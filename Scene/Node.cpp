#include "Node.h"
#include<glm\ext.hpp>


using namespace Scene;
Node::Node(int id, Renderer::Device* device)
:id(id), position(0), size(1)
{
	transformBuffer = device->createGPUBuffer(sizeof(TransformBuffer));
}


Node::~Node()
{
}


void Node::addComponent(Component* component)
{
	components.insert(component);
}


void Node::addChildNode(Node* node)
{
	children.insert(node);
}


void Node::render(Renderer::RenderContext* context, ComponentType type)
{
	transformBuffer->setData(&Resource(sizeof(TransformBuffer), &transforms));
	context->setGPUBuffer(1, transformBuffer);
	for each (Component* component in components)
	{
		if (component->getType() == type)
			component->onRender(context);
	}
	for each (Node* node in children)
	{
		node->render(context,type);
	}
}


void Node::update(double timeDelta, glm::vec3& parentPos, glm::vec3& parentSize)
{
	glm::vec3 pos = parentPos + position;
	//glm::vec3 size = parentSize * size;
	transforms.translate = glm::translate(pos);
	transforms.scale = glm::scale(size);
	for each (Component* component in components)
	{
		component->onUpdate(timeDelta);
	}
	for each (Node* node in children)
	{
		node->update(timeDelta, pos, size);
	}
}


const glm::vec3& Node::getPosition() const
{
	return position;
}


void Node::setPosition(const glm::vec3& position)
{
	this->position = position;
}


void Node::setScaling(const glm::vec3& scaling)
{
	size = scaling;
}


void Node::setRotation(const glm::quat& rotation)
{
	this->rotation = rotation;
}


const glm::vec3& Node::getScaling() const
{
	return size;
}


const glm::quat& Node::getRotation() const
{
	return rotation;
}