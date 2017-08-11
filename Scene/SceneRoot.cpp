#include "SceneRoot.h"


using namespace Scene;
Root::Root()
:activeCamera(0), directionalLight(0)
{
}


Root::~Root()
{
	for each (Node* node in children)
	{
		delete node;
	}
	if (activeCamera) delete activeCamera;
	if (directionalLight) delete directionalLight;
}


void Root::addNode(Node* node)
{
	children.insert(node);
}


void Root::renderGeometry(Renderer::RenderContext* context)
{
	if (activeCamera)
	{
		activeCamera->setInverseCameraBuffer(context);
		for each (Node* node in children)
		{
			node->render(context, ComponentType::Geometry);
		}
	}
}


void Root::renderOther(Renderer::RenderContext* context)
{
	if (activeCamera)
	{
		activeCamera->setInverseCameraBuffer(context);
		for each (Node* node in children)
		{
			node->render(context, ComponentType::Other);
		}
	}
}


void Root::renderLights(Renderer::RenderContext* context, 
	RenderFramework::DeferredRenderer* renderer)
{
	if (activeCamera)
	{
		activeCamera->setInverseCameraBuffer(context);
		if (directionalLight)
		{
			directionalLight->onRender(context);
			renderer->renderDirectionalLight();
		}
	//	context->enableDepthTesting(true);
		context->setAlphaBlendingState(Renderer::AlphaBlendAdditive);
		for each (Node* node in children)
		{
			node->render(context, ComponentType::Light);
		}
		context->setAlphaBlendingState(Renderer::AlphaBlendDisabled);
	}
}


/*bool Root::handle(const MessagePump::Message& message)
{
	if (message.type == MessagePump::MessageType::KeyPress)
	{
		if (message.state == MessagePump::MessageState::KeyDown)
		{
			if (message.y == 'W')
			{
				if (activeCamera) activeCamera->getMove().x = 1;
			}
			if (message.y == 'S')
			{
				if (activeCamera) activeCamera->getMove().x = -1;
			}
			if (message.y == 'A')
			{
				if (activeCamera) activeCamera->getMove().z = -1;
			}
			if (message.y == 'D')
			{
				if (activeCamera) activeCamera->getMove().z = 1;
			}
			if (message.y == 'Q')
			{
				if (activeCamera) activeCamera->getMove().y = 1;
			}
			if (message.y == 'Z')
			{
				if (activeCamera) activeCamera->getMove().y = -1;
			}
			return false;
		}
		else if (message.state == MessagePump::MessageState::KeyUp)
		{
			if (message.y == 'W')
			{
				if (activeCamera) activeCamera->getMove().x = 0;
			}
			if (message.y == 'S')
			{
				if (activeCamera) activeCamera->getMove().x = 0;
			}
			if (message.y == 'A')
			{
				if (activeCamera) activeCamera->getMove().z = 0;
			}
			if (message.y == 'D')
			{
				if (activeCamera) activeCamera->getMove().z = 0;
			}
			if (message.y == 'Q')
			{
				if (activeCamera) activeCamera->getMove().y = 0;
			}
			if (message.y == 'Z')
			{
				if (activeCamera) activeCamera->getMove().y = -0;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	else if (message.type == MessagePump::MessageType::MouseMove)
	{
		if (activeCamera) activeCamera->cameraLook(message);
	}
	return false;
}*/


void Root::update(double deltaTime)
{
	glm::vec3 pos(0);
	glm::vec3 size(1);
	for each (Node* node in children)
	{
		node->update(deltaTime, pos, size);
	}
}


void Root::setActiveCamera(Camera* activeCamera)
{
	this->activeCamera = activeCamera;
}


void Root::setDirectionalLight(DirectionalLight* directionalLight)
{
	this->directionalLight = directionalLight;
}