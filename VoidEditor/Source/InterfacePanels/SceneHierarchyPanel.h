#pragma once
#include "Void/ECS/Scene.h"



class SceneHierarchyPanel
{

public:

	SceneHierarchyPanel() : m_Scene(nullptr), m_SelectedEntity(nullptr) {}
	SceneHierarchyPanel(Scene* SceneRef) : m_Scene(SceneRef), m_SelectedEntity(nullptr) {}

	void SetScene(Scene* SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender();

	class EntityBase* GetSelected() const { return m_SelectedEntity; }

private:

	Scene* m_Scene;
	class EntityBase* m_SelectedEntity;
};