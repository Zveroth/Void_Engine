#pragma once
#include "Void.h"

#include "Void/ECS/Components/SpriteComponent.h"
#include "Void/ECS/Components/CameraComponent.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"



class EditorLayer : public Layer
{
public:

	EditorLayer() : Layer("Render2DLayer")/*, m_CameraController(16.0f / 9.0f)*/ {}

	virtual void OnAttach() override
	{
		const Window& AppWindow = Application::GetApp().GetWindow();

		FramebufferSpecification Spec;
		Spec.Width = AppWindow.GetWidth();
		Spec.Height = AppWindow.GetHeight();
		m_Framebuffer = Framebuffer::Create(Spec);

		m_FramebufferSize.x = Spec.Width;
		m_FramebufferSize.y = Spec.Height;

		m_Scene = CreateRef<Scene>();

		Entity& EditorCamera = m_Scene->AddEntity<Entity>(m_Scene, "Editor_Camera");
		m_Scene->SetActiveCamera(EditorCamera.AddComponent<CameraComponent>());

		Entity& Ent = m_Scene->AddEntity<Entity>(m_Scene);
		Ent.AddComponent<SpriteComponent>(glm::vec4(0.5f, 0.2f, 1.0f, 1.0f));//.AddLocationOffset(glm::vec3(0.0f, 0.0f, -5.0f));
	}

	virtual void OnUpdate(float DeltaTime) override
	{

		m_Framebuffer->Bind();
		RenderCommand::Clear();
		Renderer2D::ResetStats();

		//if (m_bViewportFocused)
		//	m_CameraController.OnUpdate(DeltaTime);

		m_Scene->Tick(DeltaTime);

		m_Framebuffer->Unbind();
	}

	virtual void OnImGuiRender() override
	{
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
			}
			ImGui::End();

			ImGui::Begin("Entities");
			{
				for (const Entity& Ent : m_Scene->GetAllEntities())
				{
					if (ImGui::Button(Ent.GetEntityFullName().c_str()))
					{
						
					}
				}
			}
			ImGui::End();

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
						if (m_Scene->HasActiveCamera())
							m_Scene->GetActiveCamera().GetCamera().SetAspectRatio(m_FramebufferSize.x / m_FramebufferSize.y);
				}

				ImGui::Image((void*)m_Framebuffer->GetColorAttachmentID(), ViewportSize, ImVec2(0, 1), ImVec2(1, 0));
			}
			ImGui::End();
			ImGui::PopStyleVar();
		}
		ImGui::End();
	}

	virtual void OnEvent(Event& e) override
	{
		m_Scene->OnEvent(e);
	}

private:

	Ref<Framebuffer> m_Framebuffer;
	ImVec2 m_FramebufferSize;

	bool m_bViewportFocused = false;

	Ref<Scene> m_Scene;
};