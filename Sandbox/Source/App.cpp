#include "Void.h"


#include "Renderer/OrthoCamera.h"
#include "imgui.h"

class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer"), m_Camera(1.6f * -2.0f, 1.6f * 2.0f, 0.9f * -2.0f, 0.9f * 2.0f), m_Rotation(0.0f) {}

	virtual void OnAttach() override
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


		BufferLayout layout = {
			{ ShaderDataType::Vec3, "a_Position" },
			{ ShaderDataType::Vec4, "a_Position" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
		#version 330 core

		layout(location = 0) in vec3 i_Position;
		layout(location = 1) in vec4 a_Color;

		uniform mat4 u_View;
		uniform mat4 u_Projection;

		out vec4 io_Color;

		void main()
		{
			gl_Position = u_Projection * u_View * vec4(i_Position, 1.0);
			io_Color = a_Color;
		}
	)";

		std::string fragmentSource = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;

		in vec4 io_Color;

		void main()
		{
			o_Color = io_Color;
		}
	)";

		m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);

		m_SquareVertexArray.reset(VertexArray::Create());

		float Svertices[] = {
			-0.75f, -0.75f, 0.0f, 1.0f, 0.2f, 0.3f, 1.0f,
			0.75f, -0.75f, 0.0f, 0.3f, 0.2f, 1.0f, 1.0f,
			0.75f, 0.75f, 0.0f, 0.2f, 1.0f, 0.3f, 1.0f,
			-0.75f, 0.75f, 0.0f, 0.3f, 0.2f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> Svb;
		Svb.reset(VertexBuffer::Create(Svertices, sizeof(Svertices)));

		Svb->SetLayout({
			{ ShaderDataType::Vec3, "a_Position" },
			{ ShaderDataType::Vec4, "a_Color" }
			});
		m_SquareVertexArray->AddVertexBuffer(Svb);


		uint32_t sindices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> Sib;
		Sib.reset(IndexBuffer::Create(sindices, 6));
		m_SquareVertexArray->SetIndexBuffer(Sib);

		m_Camera.SetPosition(glm::vec3(1.0f, 0.0f, 5.0f));
	}

	virtual void OnUpdate(const float& DeltaTime) override
	{
		VD_TRACE("{0}", DeltaTime);
		m_Rotation += 90.0f * DeltaTime;
		m_Camera.SetRotation(glm::vec3(0.0f, 0.0f, m_Rotation));

		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_SquareVertexArray, m_Shader);
		Renderer::Submit(m_VertexArray, m_Shader);

		Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Framerate");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	virtual void OnEvent(Event& e) override
	{
		
	}

private:

	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::shared_ptr<VertexArray> m_SquareVertexArray;

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