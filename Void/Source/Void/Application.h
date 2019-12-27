#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"


class VD_API Application
{

public:

	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

private:

	bool OnWindowClose(WindowCloseEvent& CloseEvent);

	std::unique_ptr<Window> m_Window;

	bool m_bRunning;

	LayerStack m_LayerStack;
};

Application* CreateApplication();