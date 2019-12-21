#include "vdpch.h"

#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	WindowResizeEvent E(1280, 720);
	VD_INFO(E.ToString());

	while (true)
	{

	}
}