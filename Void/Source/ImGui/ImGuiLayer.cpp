#include "vdpch.h"
#include "ImGuiLayer.h"
#include "Void/Core/Application.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/KeyboardEvent.h"
#include "Void/Events/MouseEvent.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"



#define ConvertColor(r, g, b) ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f)

void ImGuiLayer::OnAttach()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/Source_Sans_Pro/SourceSansPro-Regular.ttf", 16.0f);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	SetDarkThemeColors();

	Application& app = Application::GetApp();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnEvent(Event& e)
{
	if (m_bConsumeEvents)
	{
		ImGuiIO& io = ImGui::GetIO();
		e.m_bHandled |= e.IsInCategory(EEventCategory::Mouse) & io.WantCaptureMouse;
		e.m_bHandled |= e.IsInCategory(EEventCategory::Keyboard) & io.WantCaptureKeyboard;
	}
}

void ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::GetApp();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void ImGuiLayer::SetDarkThemeColors()
{
	auto& Colors = ImGui::GetStyle().Colors;

	Colors[ImGuiCol_WindowBg] =				ConvertColor(3, 0, 9);
	
	Colors[ImGuiCol_Header] =				ConvertColor(20, 0, 60);
	Colors[ImGuiCol_HeaderHovered] =		ConvertColor(30, 0, 90);
	Colors[ImGuiCol_HeaderActive] =			ConvertColor(36, 0, 108);
	
	Colors[ImGuiCol_Button] =				ConvertColor(20, 0, 60);
	Colors[ImGuiCol_ButtonHovered] =		ConvertColor(30, 0, 90);
	Colors[ImGuiCol_ButtonActive] =			ConvertColor(35, 0, 105);
	
	Colors[ImGuiCol_FrameBg] =				ConvertColor(20, 0, 60);
	Colors[ImGuiCol_FrameBgHovered] =		ConvertColor(30, 0, 90);
	Colors[ImGuiCol_FrameBgActive] =		ConvertColor(35, 0, 105);
	
	Colors[ImGuiCol_Tab] =					ConvertColor(20, 0, 60);
	Colors[ImGuiCol_TabHovered] =			ConvertColor(35, 0, 105);
	Colors[ImGuiCol_TabActive] =			ConvertColor(30, 0, 90);
	Colors[ImGuiCol_TabUnfocused] =			ConvertColor(20, 0, 60);
	Colors[ImGuiCol_TabUnfocusedActive] =	ConvertColor(30, 0, 90);
	
	Colors[ImGuiCol_TitleBg] =				ConvertColor(10, 0, 30);
	Colors[ImGuiCol_TitleBgActive] =		Colors[ImGuiCol_TitleBg];
	Colors[ImGuiCol_TitleBgCollapsed] =		ConvertColor(255, 255, 0);

	Colors[ImGuiCol_ScrollbarBg] =			Colors[ImGuiCol_WindowBg];

	Colors[ImGuiCol_PopupBg] =				Colors[ImGuiCol_WindowBg];

	Colors[ImGuiCol_MenuBarBg] =			Colors[ImGuiCol_WindowBg];

	Colors[ImGuiCol_CheckMark] =			ConvertColor(0, 255, 0);
}