#pragma once
#include "Void.h"


#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "InterfacePanels/SceneHierarchyPanel.h"
#include "InterfacePanels/DetailsPanel.h"



class EditorLayer : public Layer
{
public:

	EditorLayer() : Layer("Render2DLayer") {}
	virtual ~EditorLayer();

	virtual void OnAttach() override;

	virtual void OnUpdate(float DeltaTime) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Event& e) override;

private:

	Ref<Framebuffer> m_Framebuffer;
	ImVec2 m_FramebufferSize;

	bool m_bViewportFocused = false;

	UniqueRef<Scene> m_Scene;
	SceneHierarchyPanel m_SceneHierarchyPanel;
	DetailsPanel m_DetailsPanel;
};