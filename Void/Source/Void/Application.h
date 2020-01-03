#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"

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

	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::shared_ptr<Shader> m_SquareShader;
	std::shared_ptr<VertexArray> m_SquareVertexArray;
};

Application* CreateApplication();