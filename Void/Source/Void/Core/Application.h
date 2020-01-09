#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Void/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

class Shader;

class  Application
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
	bool OnWindowResize(WindowResizeEvent& ResizeEvent);

	std::unique_ptr<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;

	bool m_bRunning;
	bool m_bMinimized;
};

Application* CreateApplication();