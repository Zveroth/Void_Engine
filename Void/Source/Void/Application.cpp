#include "vdpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

Application::Application() : m_bRunning(true)
{
	m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application()
{

}

void Application::Run()
{
	while (m_bRunning)
	{
		m_Window->OnUpdate();
	}
}