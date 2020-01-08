#include "Void.h"


#include "Renderer/OrthoCamera.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer"), m_Camera(1.6f * -2.0f, 1.6f * 2.0f, 0.9f * -2.0f, 0.9f * 2.0f), m_Rotation(0.0f) {}

	virtual void OnAttach() override
	{
		Ref<Shader> TexShader = m_ShaderLibrary.Load("Assets/Shaders/TextureShader.glsl");

		m_SquareVertexArray.reset(VertexArray::Create());

		float vertices[] = {
			-0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
			0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
			0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
			-0.75f, 0.75f, 0.0f, 0.f, 1.0f
		};

		Ref<VertexBuffer> SVertexBuffer;
		SVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

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

		m_Camera.SetPosition(glm::vec3(1.0f, 0.0f, 5.0f));

		m_TestTexture = Texture2D::Create("Assets/Textures/test.png");
		m_TestTexture->Bind();
	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		//m_Rotation += 90.0f * DeltaTime;

		Renderer::BeginScene(m_Camera);

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
		
	}

private:

	ShaderLibrary m_ShaderLibrary;

	Ref<Texture2D> m_TestTexture;

	Ref<VertexArray> m_SquareVertexArray;

	OrthographicCamera m_Camera;

	float m_Rotation;
};

class Sandbox : public Application
{

public:

	Sandbox()
	{
		PushLayer(new ExmpLayer());
	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}