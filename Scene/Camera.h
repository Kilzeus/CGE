#pragma once
#include"Node.h"
#include"Component.h"
#include"Message.h"
#include<glm\glm.hpp>
#include<DirectXMath.h>

namespace Scene
{
	struct CameraBuffer
	{
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 position;
		float padding;

		CameraBuffer() :padding(0) {}
	};


	class Camera : public Component
	{
		glm::vec3 lookat;
		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 move; // x = forward, z = right, y = up

		Node* node;
		float speed;
		bool mouseLook;

		//matrices for rendering
		CameraBuffer camerabuffer;
		CameraBuffer inverseCameraBuffer;
		Renderer::GPUBuffer* cameraTransforms;
		Renderer::GPUBuffer* inverseCameraTransforms;
	public:
		Camera(Renderer::Device* device, bool freelook=false);
		Node* getNode();
		const glm::mat4x4& getViewMatrix();
		const glm::mat4x4& getProjectionMatrix();
		void setLookAtPosition(const glm::vec3& position);
		void setProjection(float fov, float aspectRatio, float renderRange = 1000.0f);
		void onRender(class Renderer::RenderContext* context);
		void onUpdate(double timeDelta);
		glm::vec3& getMove();
		void cameraLook(const MessagePump::Message &evt);
		void setInverseCameraBuffer(Renderer::RenderContext* context);
		void setSpeed(float speed);
	};
}