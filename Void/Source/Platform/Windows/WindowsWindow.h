#pragma once

#include "Void/Window.h"
#include "Renderer/RenderContext.h"

#include "GLFW/glfw3.h"


class WindowWindow : public Window
{

public:

	WindowWindow(const WindowProperties& Properties);
	virtual ~WindowWindow();

	virtual void OnUpdate() override;

	inline virtual unsigned int GetWidth() const override { return m_Data.Width; }
	inline virtual unsigned int GetHeight() const override { return m_Data.Height; }

	inline virtual void SetEventCallback(const std::function<void(Event&)>& Callback) override { m_Data.EventCallback = Callback; }
	void virtual SetVSync(bool bEnabled) override;
	bool virtual IsVSyncEnabled() const override;

	inline virtual void* GetNativeWindow() const override { return m_Window; };

private:

	virtual void Init(const WindowProperties& Properties);
	virtual void Shutdown();

	GLFWwindow* m_Window;
	RenderContext* m_Context;

	struct WindowData
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool bVSync;

		std::function<void(Event&)> EventCallback;
	};

	WindowData m_Data;
};