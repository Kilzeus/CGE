#pragma once
#include"Component.h"
#include"Device.h"
#include<glm\glm.hpp>
#include<glm\ext.hpp>
#include<set>
namespace Scene
{

	struct TransformBuffer
	{
		glm::mat4 scale;
		glm::mat4 rotate;
		glm::mat4 translate;
	};
	/*
		Node is a point containing components and has a transform.
	*/
	class Node
	{
		int id;
		TransformBuffer transforms;
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 size;

		std::set<Component*> components;
		std::set<Node*> children;

		Renderer::GPUBuffer* transformBuffer;
	public:
		Node(int id, Renderer::Device* device);
		~Node();
		void addComponent(Component* component);
		void addChildNode(Node* node);
		void render(Renderer::RenderContext* context, ComponentType type);
		void update(double timeDelta, glm::vec3& parentPos, glm::vec3& parentSize);
		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3& position);
		const glm::vec3& getScaling() const;
		void setScaling(const glm::vec3& scaling);
		const glm::quat& getRotation() const;
		void setRotation(const glm::quat& rotation);
	};
}
