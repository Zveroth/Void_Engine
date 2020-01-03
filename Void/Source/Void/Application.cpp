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

	int index = 0;
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponenetCount(), GL_FLOAT, GL_FALSE, layout.GetStride(), (const void*)element.Offset);
		index++;
	}

	uint32_t indices[3] = {
		0, 1, 2
	};

	m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

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

		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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