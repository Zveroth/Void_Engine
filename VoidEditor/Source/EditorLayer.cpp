#include "vdepch.h"
#include "EditorLayer.h"
#include "Void/ECS/Components/TransformComponent.h"
#include "Void/ECS/Components/SpriteComponent.h"
#include "Void/ECS/Components/CameraComponent.h"



EditorLayer::~EditorLayer()
{

}

void EditorLayer::OnAttach()
{
	const Window& AppWindow = Application::GetApp().GetWindow();

	FramebufferSpecification Spec;
	Spec.Width = AppWindow.GetWidth();
	Spec.Height = AppWindow.GetHeight();
	m_Framebuffer = Framebuffer::Create(Spec);

	m_FramebufferSize.x = Spec.Width;
	m_FramebufferSize.y = Spec.Height;

	m_Scene = CreateUnique<Scene>();

	m_SceneHierarchyPanel.SetScene(m_Scene.get());
	m_DetailsPanel.SetScene(m_Scene.get());
}

void EditorLayer::OnUpdate(float DeltaTime)
{
	m_Framebuffer->Bind();
	RenderCommand::Clear();
	Renderer2D::ResetStats();

	m_Scene->Tick(DeltaTime);

	m_Framebuffer->Unbind();
}


//#define DRAW_COLOR_MANAGEMENT

void EditorLayer::OnImGuiRender()
{
#ifdef DRAW_COLOR_MANAGEMENT
#define AAAAA(A) ImGui::ColorPicker4(#A, &Style.Colors[A].x);

	ImGui::Begin("A");
	{
		auto& Style = ImGui::GetStyle();
		AAAAA(ImGuiCol_WindowBg);
		AAAAA(ImGuiCol_Header);
		AAAAA(ImGuiCol_HeaderHovered);
		AAAAA(ImGuiCol_HeaderActive);
		
		AAAAA(ImGuiCol_Button);
		AAAAA(ImGuiCol_ButtonHovered);
		AAAAA(ImGuiCol_ButtonActive);
		
		AAAAA(ImGuiCol_FrameBg);
		AAAAA(ImGuiCol_FrameBgHovered);
		AAAAA(ImGuiCol_FrameBgActive);
		
		AAAAA(ImGuiCol_Tab);
		AAAAA(ImGuiCol_TabHovered);
		AAAAA(ImGuiCol_TabActive);
		AAAAA(ImGuiCol_TabUnfocused);
		AAAAA(ImGuiCol_TabUnfocusedActive);
		
		AAAAA(ImGuiCol_TitleBg);
		AAAAA(ImGuiCol_TitleBgActive);
		AAAAA(ImGuiCol_TitleBgCollapsed);

		AAAAA(ImGuiCol_CheckMark);
	}
	ImGui::End();
#endif // DRAW_COLOR_MANAGEMENT

	static bool open = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace Demo", &open, window_flags);
	{
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				if (ImGui::MenuItem("Exit"))	Application::GetApp().Exit();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		Renderer2D::BatchStats Stats = Renderer2D::GetStats();

		ImGui::Begin("Statistics");
		{
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::Text("Renderer 2D:");
			ImGui::Text("Draw calls: %d", Stats.DrawCalls);
			ImGui::Text("Quads: %d", Stats.QuadCount);
			ImGui::Text("Vertices: %d", Stats.GetVertexCount());
			ImGui::Text("Indices: %d", Stats.GetIndexCount());

			ImGui::Button("SomeButton");
		}
		ImGui::End();

		m_SceneHierarchyPanel.OnImGuiRender();
		m_DetailsPanel.OnImGuiRender(m_SceneHierarchyPanel.GetSelected());

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");
		{
			m_bViewportFocused = ImGui::IsWindowFocused();
			Application::GetApp().GetImGuiLayer()->SetConsumeEvents(!m_bViewportFocused);

			ImVec2 ViewportSize = ImGui::GetContentRegionAvail();
			if (ViewportSize.x != m_FramebufferSize.x || ViewportSize.y != m_FramebufferSize.y)
			{
				m_FramebufferSize = ViewportSize;

				if (m_Framebuffer->Resize(m_FramebufferSize.x, m_FramebufferSize.y))
					m_Scene->SetViewportAspectRatio(m_FramebufferSize.x / m_FramebufferSize.y);
			}

			ImGui::Image((void*)m_Framebuffer->GetColorAttachmentID(), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
	ImGui::End();

//	ImGui::ShowDemoWindow();
}

void EditorLayer::OnEvent(Event& e)
{
	m_Scene->OnEvent(e);
}