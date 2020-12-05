#include "Void.h"
#include "Void/EntryPoint.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"


class Render2DLayer : public Layer
{
public:

	Render2DLayer() : Layer("Render2DLayer"), CameraController(16.0f / 9.0f), m_SpriteCount(10.0f) {}

	virtual void OnAttach() override
	{
		m_Texture = Texture2D::Create("Assets/Textures/test.png");
	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		CameraController.OnUpdate(DeltaTime);

		Renderer2D::BeginScene(CameraController.GetCamera());

		for (float X = -(m_SpriteCount / 2.0f) + 1.0f; X <= (m_SpriteCount / 2.0f); X += 1.0f)
		{
			for (float Y = -(m_SpriteCount / 2.0f) + 1.0f; Y <= (m_SpriteCount / 2.0f); Y += 1.0f)
			{
				Renderer2D::DrawQuad({ 0.03f * X, 0.03f * Y }, { 0.01f, 0.01f }, { (X + (m_SpriteCount / 2.0f)) / m_SpriteCount , (Y + (m_SpriteCount / 2.0f)) / m_SpriteCount, 0.0f, 1.0f });
			}
		}

		Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_Texture);

		Renderer2D::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Framerate");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	virtual void OnEvent(Event& e) override
	{
		CameraController.OnEvent(e);
	}

private:

	OrthographicCameraController CameraController;

	float m_SpriteCount;

	Ref<Texture2D> m_Texture;
};

class Sandbox : public Application
{

public:

	Sandbox()
	{
		PushLayer(new Render2DLayer());
	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}