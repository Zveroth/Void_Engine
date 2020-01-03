#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

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

	std::unique_ptr<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;

	bool m_bRunning;

	unsigned int m_VertexArray;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr <VertexBuffer> m_VertexBuffer;
	std::unique_ptr <IndexBuffer> m_IndexBuffer;
};

Application* CreateApplication();