#pragma once

#include "Void/ECS/Scene.h"


class DetailsPanel
{

public:

	DetailsPanel() {}
	DetailsPanel(const Ref<Scene>& OwningScene) : m_Scene(OwningScene) {}

	void SetScene(const Ref<Scene>& SceneRef) { m_Scene = SceneRef; }

	void OnImGuiRender(int32_t Selected);

private:

	WeakRef<Scene> m_Scene;
};