#pragma once

#include "Void/Window.h"

#include "GLFW/glfw3.h"


class WindowWindow : public Window
{

public:

	WindowWindow(const WindowProperties& Properties);
	virtual ~WindowWindow();

	void OnUpdate() override;

	inline unsigned int GetWidth() const override { return m_Data.Width; }
	inline unsigned int GetHeight() const override { return m_Data.Height; }

	inline void SetEventCallback(const std::function<void(Event&)>& Callback) override { m_Data.EventCallback = Callback; }
	void SetVSync(bool bEnabled) override;
	bool IsVSyncEnabled() const override;

private:

	virtual void Init(const WindowProperties& Properties);
	virtual void Shutdown();

	GLFWwindow* m_Window;

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