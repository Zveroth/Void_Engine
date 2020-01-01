#include "vdpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"



OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window)
{
	VD_CORE_ASSERT(m_WindowHandle, "Window for context is null!");
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	VD_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");
	VD_CORE_INFO("OpenGLContext initialized");
	VD_CORE_TRACE("	Vendor: {0}", glGetString(GL_VENDOR));
	VD_CORE_TRACE("	Renderer: {0}", glGetString(GL_RENDERER));
	VD_CORE_TRACE("	Version: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}