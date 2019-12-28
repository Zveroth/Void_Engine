#include "vdpch.h"
#include "WindowsInput.h"

#include "Void/Application.h"
#include "GLFW/glfw3.h"


Input* Input::s_Instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(int keycode)
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, keycode);

	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool WindowsInput::IsMouseButtonPressedImpl(int button)
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, button);

	return (state == GLFW_PRESS);
}

std::pair<float, float> WindowsInput::GetMousePosImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return std::pair<float, float>(xPos, yPos);
}

float WindowsInput::GetMouseXImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)xPos;
}

float WindowsInput::GetMouseYImpl()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)yPos;
}
