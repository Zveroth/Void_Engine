#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"


class VD_API Application
{

public:

	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

	inline Window& GetWindow() const { return *m_Window; }
	inline static Application& GetApp() { return *s_Instance; }

private:

	static Application* s_Instance;

	bool OnWindowClose(WindowCloseEvent& CloseEvent);

	std::unique_ptr<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;

	bool m_bRunning;

	LayerStack m_LayerStack;
};

Application* CreateApplication();