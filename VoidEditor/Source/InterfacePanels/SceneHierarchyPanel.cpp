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
			DynamicArray<ControlledPointer<EntityBase>> Entities = m_Scene->GetEntities();

			for(const ControlledPointer<EntityBase>& Entity : Entities)
			{
				if (ImGui::Selectable(Entity->GetEntityName().c_str(), (m_SelectedEntity == Entity)))
				{
					m_SelectedEntity = Entity;
				}

				if (ImGui::BeginPopupContextItem(0))
				{
					if (ImGui::MenuItem("Delete Entity"))
					{
						Entity->Destroy();

						if (m_SelectedEntity == Entity)
							m_SelectedEntity.Clear();
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