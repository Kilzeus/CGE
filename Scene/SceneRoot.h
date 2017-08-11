#pragma once
#include"Node.h"
#include"Camera.h"
#include"DirectionalLight.h"
#include"MessageListener.h"
#include"DeferredRenderer.h"


namespace Scene
{
	class Root
	{
		std::set<Node*> children;
		Camera* activeCamera;
		DirectionalLight* directionalLight;
	public:
		Root();
		~Root();
		void addNode(Node* node);
		void renderGeometry(Renderer::RenderContext* context);
		void renderOther(Renderer::RenderContext* context);
		void renderLights(Renderer::RenderContext* context, 
			RenderFramework::DeferredRenderer* renderer);
		void update(double deltaTime);
		//bool handle(const MessagePump::Message& message);
		void setActiveCamera(Camera* activeCamera);
		void setDirectionalLight(DirectionalLight* directionalLight);
	};
}