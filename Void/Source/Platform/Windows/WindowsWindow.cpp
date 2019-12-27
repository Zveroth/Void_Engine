#include "vdpch.h"
#include "WindowsWindow.h"

#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/MouseEvent.h"
#include "Void/Events/KeyboardEvent.h"


static bool bGLFWInitialized = false;

static void GLFWErrorCallback(int Error, const char* Description)
{
	VD_CORE_ERROR("GLFW Error ({0}): {1}", Error, Description);
}


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

	glfwSetErrorCallback(GLFWErrorCallback);

	m_Window = glfwCreateWindow(Properties.Width, Properties.Height, Properties.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	glClearColor(0.1, 0.1, 0.1, 1);

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);
			Data.Width = Width;
			Data.Height = Height;

			WindowResizeEvent ResizeEvent(Width, Height);
			Data.EventCallback(ResizeEvent);
		}
	);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent CloseEvent;
			Data.EventCallback(CloseEvent);
		}
	);

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent PressEvent(key, 0);
					Data.EventCallback(PressEvent);
				}
				break;

				case GLFW_RELEASE:
				{
					KeyReleasedEvent ReleaseEvent(key);
					Data.EventCallback(ReleaseEvent);
				}
				break;

				case GLFW_REPEAT:
				{
					KeyPressedEvent PressEvent(key, 1);
					Data.EventCallback(PressEvent);
				}
				break;
			}
		}
	);

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent PressEvent(button);
					Data.EventCallback(PressEvent);
				}
				break;

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent ReleaseEvent(button);
					Data.EventCallback(ReleaseEvent);
				}
				break;
			}
		}
	);

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent ScrollEvent((float)xOffset, (float)yOffset);
			Data.EventCallback(ScrollEvent);
		}
	);

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& Data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent MoveEvent((float)xPos, (float)yPos);
			Data.EventCallback(MoveEvent);
		}
	);
}

void WindowWindow::Shutdown()
{
	glfwDestroyWindow(m_Window);
}