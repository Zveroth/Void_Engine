#pragma once
#include "Void/ECS/Scene.h"
#include "Void/ECS/EntityBase.h"



class SceneHierarchyPanel
{

public:

	SceneHierarchyPanel() : m_Scene(nullptr), m_SelectedEntity() {}
	SceneHierarchyPanel(Scene* SceneRef) : m_Scene(SceneRef), m_SelectedEntity() {}

	void SetScene(Scene* SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender();

	ControlledPointer<EntityBase>& GetSelected() { return m_SelectedEntity; }
	const ControlledPointer<EntityBase>& GetSelected() const { return m_SelectedEntity; }

private:

	Scene* m_Scene;
	ControlledPointer<EntityBase> m_SelectedEntity;
};