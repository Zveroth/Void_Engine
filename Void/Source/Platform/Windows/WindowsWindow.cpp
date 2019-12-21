#include "vdpch.h"
#include "WindowsWindow.h"


static bool bGLFWInitialized = false;

Window* Window::Create(const WindowProperties& Properties)
{
	return new WindowWindow(Properties);
}

WindowWindow::WindowWindow(const WindowProperties& Properties)
{
	Init(Properties);
}

WindowWindow::~WindowWindow()
{
	Shutdown();
}

void WindowWindow::OnUpdate()
{
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(m_Window);
}

void WindowWindow::SetVSync(bool bEnabled)
{
	if (bEnabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.bVSync = bEnabled;
}

bool WindowWindow::IsVSyncEnabled() const
{
	return m_Data.bVSync;
}

void WindowWindow::Init(const WindowProperties& Properties)
{
	m_Data.Title = Properties.Title;
	m_Data.Width = Properties.Width;
	m_Data.Height = Properties.Height;

	VD_CORE_INFO("Createing window {0} ({1}, {2})", Properties.Title, Properties.Width, Properties.Height);

	if (!bGLFWInitialized)
	{
		VD_CORE_ASSERT(glfwInit(), "Couldn't initialize GLFW");

		bGLFWInitialized = true;
	}

	m_Window = glfwCreateWindow(Properties.Width, Properties.Height, Properties.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	glClearColor(0.1, 0.1, 0.1, 1);
}

void WindowWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
}