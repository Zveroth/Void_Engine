#include "Void.h"
#include "Void/EntryPoint.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer"), m_CameraController(16.0f/ 9.0f), m_Rotation(0.0f) {}

	virtual void OnAttach() override
	{
		Ref<Shader> TexShader = m_ShaderLibrary.Load("Assets/Shaders/TextureShader.glsl");

		m_SquareVertexArray = VertexArray::Create();

		float vertices[] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f, 0.75f, 0.0f, 0.f, 1.0f
		};

		Ref<VertexBuffer> SVertexBuffer;
		SVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

		SVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "i_Position" },
			{ ShaderDataType::Vec2, "i_TexCoord" }
			});
		m_SquareVertexArray->AddVertexBuffer(SVertexBuffer);


		uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> SIndexBuffer;
		SIndexBuffer.reset(IndexBuffer::Create(indices, 6));
		m_SquareVertexArray->SetIndexBuffer(SIndexBuffer);

		//m_CameraController.SetPosition(glm::vec3(1.0f, 0.0f, 5.0f));

		m_TestTexture = Texture2D::Create("Assets/Textures/test.png");
		m_TestTexture->Bind();
	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		m_CameraController.OnUpdate(DeltaTime);

		Renderer::BeginScene(m_CameraController.GetCamera());

		Ref<Shader> TexShader = m_ShaderLibrary.Get("TextureShader");
		std::static_pointer_cast<OpenGLShader>(TexShader)->Bind();
		glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0));
		Model = glm::rotate(Model, glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		std::static_pointer_cast<OpenGLShader>(TexShader)->UploadUniform("u_Model", Model);
		std::static_pointer_cast<OpenGLShader>(TexShader)->UploadUniform("u_Texture", 0);
		Renderer::Submit(m_SquareVertexArray, TexShader);

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Framerate");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	virtual void OnEvent(Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:

	ShaderLibrary m_ShaderLibrary;

	Ref<Texture2D> m_TestTexture;

	Ref<VertexArray> m_SquareVertexArray;

	OrthographicCameraController m_CameraController;

	float m_Rotation;
};

class Render2DLayer : public Layer
{
public:

	Render2DLayer() : Layer("Render2DLayer"), m_CameraController(16.0f / 9.0f), m_Rotation(0.0f) {}

	virtual void OnAttach() override
	{

	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		m_CameraController.OnUpdate(DeltaTime);

		Renderer2D::BeginScene(m_CameraController.GetCamera());

		Renderer2D::DrawQuad({ -0.1f, 0.0f }, { 0.5f, 0.5f }, { 0.3f, 0.3f, 0.6f, 1.0f });
		Renderer2D::DrawQuad({ 0.2f, 0.3f }, { 0.3f, 0.3f }, { 0.4f, 0.7f, 0.1f, 1.0f });
		Renderer2D::DrawQuad({ 0.1f, -0.1f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 0.25f });

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
		m_CameraController.OnEvent(e);
	}

private:

	OrthographicCameraController m_CameraController;

	float m_Rotation;
};

class Sandbox : public Application
{

public:

	Sandbox()
	{
		//PushLayer(new ExmpLayer());
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