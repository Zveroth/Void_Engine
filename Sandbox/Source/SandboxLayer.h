#pragma once
#include "Void.h"

#include "imgui.h"


class SandboxLayer : public Layer
{
public:

	SandboxLayer() : Layer("Render2DLayer") {}

	virtual void OnAttach() override
	{

	}

	virtual void OnUpdate(float DeltaTime) override
	{
		m_FB->Bind();
		RenderCommand::Clear();

		Renderer2D::ResetStats();
		//Renderer2D::BeginScene(CameraController.GetCamera());

		//Renderer2D::EndScene();
		m_FB->Unbind();
	}

	virtual void OnImGuiRender() override
	{

	}

	virtual void OnEvent(Event& e) override
	{
		
	}

private:

	Ref<Framebuffer> m_FB;
};