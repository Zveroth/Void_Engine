#include "vdpch.h"

#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Time.h"
#include "Void/Utility/RandomGenerator.h"

#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "assimp/Importer.hpp"

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& Name) : m_bRunning(true) , m_bMinimized(false)
{
	VD_CORE_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window = std::unique_ptr<Window>(Window::Create(Name));
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	m_Window->SetVSync(false);

	Renderer::Init();

	Random::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{

}

void Application::Run()
{
	RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	Time::Init();

	while (m_bRunning)
	{

		if (!m_bMinimized)
		{
			float DeltaTime = Time::GetFrameTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(DeltaTime);


			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		}

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
	Dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	{
		if (e.m_bHandled)
			break;
		(*--it)->OnEvent(e);
	}
}

bool Application::OnWindowClose(WindowCloseEvent& CloseEvent)
{
	m_bRunning = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& ResizeEvent)
{
	if (ResizeEvent.GetWidth() == 0 || ResizeEvent.GetHeight() == 0)
	{
		m_bMinimized = true;
		return false;
	}

	m_bMinimized = false;
	Renderer::OnWindowResize(ResizeEvent.GetWidth(), ResizeEvent.GetHeight());

	return false;
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

void Application::Exit()
{
	m_bRunning = false;
}