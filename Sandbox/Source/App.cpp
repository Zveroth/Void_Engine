#include "Void.h"
#include "Void/EntryPoint.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

static bool Switcher = false;

class Render2DLayer : public Layer
{
public:

	Render2DLayer() : Layer("Render2DLayer"), CameraController(16.0f / 9.0f), m_SpriteCount(100.0f), m_Rotation(0.0f) {}

	virtual void OnAttach() override
	{
		m_Texture = Texture2D::Create("Assets/Textures/test.png");
	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		CameraController.OnUpdate(DeltaTime);

		m_Rotation += DeltaTime;

		Renderer2D::ResetStats();
		Renderer2D::BeginScene(CameraController.GetCamera());

		if (Switcher)
		{
			for (float X = -(m_SpriteCount / 2.0f) + 1.0f; X <= (m_SpriteCount / 2.0f); X += 1.0f)
			{
				for (float Y = -(m_SpriteCount / 2.0f) + 1.0f; Y <= (m_SpriteCount / 2.0f); Y += 1.0f)
				{
					Renderer2D::DrawQuad({ 0.03f * X, 0.03f * Y }, { 0.01f, 0.01f }, m_Rotation, { (X + (m_SpriteCount / 2.0f)) / m_SpriteCount , (Y + (m_SpriteCount / 2.0f)) / m_SpriteCount, 0.0f, 1.0f });
				}
			}
		}
		else
		{
			for (float X = -(m_SpriteCount / 2.0f) + 1.0f; X <= (m_SpriteCount / 2.0f); X += 1.0f)
			{
				for (float Y = -(m_SpriteCount / 2.0f) + 1.0f; Y <= (m_SpriteCount / 2.0f); Y += 1.0f)
				{
					Renderer2D::DrawQuad({ 0.03f * X, 0.03f * Y }, { 0.015f, 0.015f }, { (X + (m_SpriteCount / 2.0f)) / m_SpriteCount , (Y + (m_SpriteCount / 2.0f)) / m_SpriteCount, 0.0f, 1.0f });
				}
			}
		}


		Renderer2D::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		Renderer2D::BatchStats Stats = Renderer2D::GetStats();

		ImGui::Begin("Statistics");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Renderer 2D:");
		ImGui::Text("Draw calls: %d", Stats.DrawCalls);
		ImGui::Text("Quads: %d", Stats.QuadCount);
		ImGui::Text("Vertices: %d", Stats.GetVertexCount());
		ImGui::Text("Indices: %d", Stats.GetIndexCount());

		ImGui::End();

		ImGui::Begin("Details");
		ImGui::Checkbox("Switcher", &Switcher);
		ImGui::End();
	}

	virtual void OnEvent(Event& e) override
	{
		CameraController.OnEvent(e);
	}

private:

	OrthographicCameraController CameraController;

	float m_SpriteCount;
	float m_Rotation;

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