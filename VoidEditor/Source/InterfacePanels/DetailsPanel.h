#pragma once

#include "Void/ECS/Scene.h"


class DetailsPanel
{

public:

	DetailsPanel() : m_Scene(nullptr) {}
	DetailsPanel(Scene* OwningScene) : m_Scene(OwningScene) {}

	void SetScene(Scene* SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender(EntityBase* SelectedEntity);

private:

	Scene* m_Scene;
};