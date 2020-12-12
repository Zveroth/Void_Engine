#include "vdpch.h"
#include "Void/Core/Input.h"

#include "Void/Core/Application.h"
#include "GLFW/glfw3.h"



bool Input::IsKeyPressed(int keycode)
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, keycode);

	return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressed(int button)
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	int state = glfwGetMouseButton(window, button);

	return (state == GLFW_PRESS);
}

std::pair<float, float> Input::GetMousePos()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return std::pair<float, float>(xPos, yPos);
}

float Input::GetMouseX()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)xPos;
}

float Input::GetMouseY()
{
	auto window = static_cast<GLFWwindow*>(Application::GetApp().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)yPos;
}
