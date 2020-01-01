#include "vdpch.h"

#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"


#include "Renderer/Shader.h"
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

	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

	unsigned int indices[3] = {
		0, 1, 2
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vertexSource = R"(
		#version 330 core

		layout(location = 0) in vec3 i_Position;

		void main()
		{
			gl_Position = vec4(i_Position, 1.0);
		}
	)";

	std::string fragmentSource = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;

		void main()
		{
			o_Color = vec4(0.5, 0.2, 0.8, 1.0);
		}
	)";

	m_Shader = std::make_unique<Shader>(vertexSource, fragmentSource);
}

Application::~Application()
{

}

void Application::Run()
{
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	m_Shader->Bind();

	while (m_bRunning)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VertexArray);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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