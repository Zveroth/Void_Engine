#pragma once

#include "Core.h"
#include "Window.h"


class VD_API Application
{

public:

	Application();
	virtual ~Application();

	void Run();

private:

	std::unique_ptr<Window> m_Window;

	bool m_bRunning;
};

Application* CreateApplication();