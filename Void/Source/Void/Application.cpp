#include "vdpch.h"

#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"


#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "glad/glad.h"

Application* Application::s_Instance = nullptr;

Application::Application() : m_bRunning(true)
{
	VD_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);

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

		out vec4 io_Color;

		void main()
		{
			gl_Position = vec4(i_Position, 1.0);
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
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
		0.75f, 0.75f, 0.0f,
		-0.75f, 0.75f, 0.0f
	};

	std::shared_ptr<VertexBuffer> Svb;
	Svb.reset(VertexBuffer::Create(Svertices, sizeof(Svertices)));

	Svb->SetLayout({
		{ ShaderDataType::Vec3, "a_Position" }
	});
	m_SquareVertexArray->AddVertexBuffer(Svb);


	uint32_t sindices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	std::shared_ptr<IndexBuffer> Sib;
	Sib.reset(IndexBuffer::Create(sindices, 6));
	m_SquareVertexArray->SetIndexBuffer(Sib);

	std::string SvertexSource = R"(
		#version 330 core

		layout(location = 0) in vec3 i_Position;

		void main()
		{
			gl_Position = vec4(i_Position, 1.0);
		}
	)";

	std::string SfragmentSource = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;

		void main()
		{
			o_Color = vec4(0.6, 0.6, 0.2, 1.0);
		}
	)";

	m_SquareShader = std::make_unique<Shader>(SvertexSource, SfragmentSource);
}

Application::~Application()
{

}

void Application::Run()
{
	RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	while (m_bRunning)
	{
		RenderCommand::Clear();

		Renderer::BeginScene();

		m_SquareShader->Bind();
		Renderer::Submit(m_SquareVertexArray);

		m_Shader->Bind();
		Renderer::Submit(m_VertexArray);

		Renderer::EndScene();

		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

	//VD_CORE_TRACE("{0}", e.ToString());

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		(*--it)->OnEvent(e);
		if (e.m_bHandled)
			break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& CloseEvent)
{
	m_bRunning = false;
	return true;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}