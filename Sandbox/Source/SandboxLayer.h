#pragma once
#include "Void.h"

#include "imgui.h"


class SandboxLayer : public Layer
{
public:

	SandboxLayer() : Layer("Render2DLayer"), CameraController(16.0f / 9.0f) {}

	virtual void OnAttach() override
	{

	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		CameraController.OnUpdate(DeltaTime);

		m_FB->Bind();
		RenderCommand::Clear();

		Renderer2D::ResetStats();
		Renderer2D::BeginScene(CameraController.GetCamera());

		Renderer2D::EndScene();
		m_FB->Unbind();
	}

	virtual void OnImGuiRender() override
	{

	}

	virtual void OnEvent(Event& e) override
	{
		CameraController.OnEvent(e);
	}

private:

	OrthographicCameraController CameraController;

	Ref<Texture2D> m_Texture;
	Ref<Framebuffer> m_FB;
};