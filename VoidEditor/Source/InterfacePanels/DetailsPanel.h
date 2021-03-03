#pragma once

#include "Void/ECS/Scene.h"


class DetailsPanel
{

public:

	DetailsPanel() : m_Scene(nullptr) {}
	DetailsPanel(Scene* OwningScene) : m_Scene(OwningScene) {}

	void SetScene(Scene* SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender(ControlledPointer<EntityBase>& SelectedEntity);

private:

	template<typename T>
	void DrawAddComponent(ControlledPointer<EntityBase>& Entity);

	Scene* m_Scene;
};