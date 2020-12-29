#include "vdepch.h"
#include "SceneHierarchyPanel.h"
#include "imgui.h"
#include "Void/ECS/Entity.h"



void SceneHierarchyPanel::OnImGuiRender()
{
	if (Ref<Scene> SceneRef = m_Scene.lock())
	{
		ImGui::Begin("Entity list");
		{
			std::vector<Entity*>& Entities = SceneRef->GetRegistry()->GetAllEntities();

			for (size_t I = 0; I < Entities.size(); I++)
			{
				if (ImGui::Selectable(Entities[I]->GetEntityFullName().c_str(), (m_SelectedID == *Entities[I])))
					m_SelectedID = *Entities[I];

				if (ImGui::BeginPopupContextItem(0, 1))
				{
					if (ImGui::MenuItem("Delete Entity"))
					{
						if (m_SelectedID = *Entities[I])
							m_SelectedID = ENTITY_ID_NONE;

						SceneRef->GetRegistry()->DeleteEntity(Entities[I]);
					}

					ImGui::EndPopup();
				}
			}

			if (ImGui::BeginPopupContextWindow(0, 1, false))
			{
				if (ImGui::MenuItem("Create Entity"))
					SceneRef->AddEntity<Entity>();

				ImGui::EndPopup();
			}
		}
		ImGui::End();
	}
}