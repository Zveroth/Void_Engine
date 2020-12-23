#pragma once
#include "Void/ECS/Scene.h"



class SceneHierarchyPanel
{

public:

	SceneHierarchyPanel() {}
	SceneHierarchyPanel(const Ref<Scene>& SceneRef) : m_Scene(SceneRef) {}

	void SetScene(const Ref<Scene>& SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender();

private:

	WeakRef<Scene> m_Scene;
	uint32_t m_SelectedID = 0;
};