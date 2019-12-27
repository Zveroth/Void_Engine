#include "vdpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"



Application::Application() : m_bRunning(true)
{
	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Application::~Application()
{

}

void Application::Run()
{
	while (m_bRunning)
	{
		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher Dispatcher(e);
	Dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

	VD_CORE_TRACE("{0}", e.ToString());

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
	m_LayerStack, PushLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}