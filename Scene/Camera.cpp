#include"Camera.h"
#include<glm\ext.hpp>


using namespace Scene;
Camera::Camera(Renderer::Device* device, bool freelook)
:move(0.f, 0.f, 0.f), up(0.f, 1.f, 0.f),
lookat(0.f, 0.f, 1.f), mouseLook(freelook), speed(100.f)
{
	node = new Node(0, device);
	node->addComponent(this);
	cameraTransforms = device->createGPUBuffer(sizeof(CameraBuffer));
	inverseCameraTransforms = device->createGPUBuffer(sizeof(CameraBuffer));
	camerabuffer.position = glm::vec3(0, 0, 0);
}


Node* Camera::getNode()
{

	return node;
	
}


void Camera::onRender(Renderer::RenderContext* context)
{
	cameraTransforms->setData(&Resource(sizeof(CameraBuffer), &camerabuffer));
	context->setGPUBuffer(0, cameraTransforms);
}


void Camera::setProjection(float fov, float aspectRatio, float maxRange)
{
	camerabuffer.projectionMatrix = glm::perspective(fov, aspectRatio, 1.f, maxRange);
}


const glm::mat4& Camera::getViewMatrix()
{
	return camerabuffer.viewMatrix;
}


const glm::mat4& Camera::getProjectionMatrix()
{
	return camerabuffer.projectionMatrix;
}


void Camera::setInverseCameraBuffer(Renderer::RenderContext* context)
{
	inverseCameraBuffer.position = node->getPosition();
	inverseCameraBuffer.viewMatrix = glm::inverse(camerabuffer.viewMatrix);
	inverseCameraBuffer.projectionMatrix = glm::inverse(camerabuffer.projectionMatrix);
	inverseCameraTransforms->setData(&Resource(sizeof(CameraBuffer), &inverseCameraBuffer));
	context->setGPUBuffer(3, inverseCameraTransforms);
}


void Camera::onUpdate(double timeDelta)
{
	if (glm::length(move)>0.05f)
	{
		glm::vec3 pos = node->getPosition();
		glm::vec3 facing = lookat - pos;
		facing = glm::normalize(facing);
		pos += (facing * move.x * (float)timeDelta) * speed;
		right = glm::cross(facing,up);
		pos += right * move.z * (float)timeDelta * speed;
		pos += up * move.y * (float)timeDelta * speed;
		if (mouseLook)
		{
			lookat += right * move.z * (float)timeDelta * speed;
			lookat += up * move.y * (float)timeDelta * speed;;
		}
		node->setPosition(pos);
		camerabuffer.position = pos;
	}
	camerabuffer.viewMatrix = glm::lookAt(node->getPosition(), lookat, up);
}


void Camera::setLookAtPosition(const glm::vec3& position)
{
	lookat = position;
}


void Camera::cameraLook(const MessagePump::Message &evt)
{
	if (mouseLook)
	{
		MessagePump::MouseMessage msg = (MessagePump::MouseMessage&)evt;
		glm::vec3 facing = lookat - node->getPosition();
		facing = glm::normalize(facing);
		glm::vec2 rot(msg.relativePosition.x, msg.relativePosition.y);
		glm::vec3 rotation;

		rotation.y = atan2(facing.z, facing.x) - rot.x * 4.f;
		facing.x = cos(rotation.y);
		facing.z = sin(rotation.y);
		this->lookat = node->getPosition() + facing;
	}
}


glm::vec3& Camera::getMove()
{
	return move;
}

void Camera::setSpeed(float speed)
{
	this->speed = speed;
}