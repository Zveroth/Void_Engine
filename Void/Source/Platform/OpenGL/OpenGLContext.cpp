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
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}