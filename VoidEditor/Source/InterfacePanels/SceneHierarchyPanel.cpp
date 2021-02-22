#include "vdepch.h"
#include "SceneHierarchyPanel.h"
#include "imgui.h"
#include "Void/ECS/EntityBase.h"



void SceneHierarchyPanel::OnImGuiRender()
{
	ImGui::Begin("Entity list");
	{
		if (m_Scene)
		{
			DynamicArray<EntityBase*> Entities = m_Scene->GetEntities();

			for(EntityBase* Entity : Entities)
			{
				if (ImGui::Selectable(Entity->GetEntityName().c_str(), (m_SelectedEntity == Entity)))
				{
					m_SelectedEntity = Entity;
				}

				if (ImGui::BeginPopupContextItem(0))
				{
					if (ImGui::MenuItem("Delete Entity"))
					{
						m_SelectedEntity->Destroy();

						if (m_SelectedEntity == Entity)
							m_SelectedEntity = nullptr;
					}

					ImGui::EndPopup();
				}
			}

			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create Entity"))
					m_Scene->CreateEntity<EntityBase>();

				ImGui::EndPopup();
			}
		}
	}
	ImGui::End();
}