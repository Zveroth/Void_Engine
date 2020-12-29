#include "vdepch.h"
#include "DetailsPanel.h"
#include "imgui.h"
#include "Void/ECS/ECSRegistry.h"



void DetailsPanel::OnImGuiRender(int32_t Selected)
{
	ImGui::Begin("Details");
	{
		if (Selected != ENTITY_ID_NONE)
		{
			if (Ref<Scene> SceneRef = m_Scene.lock())
			{
				Entity* Ent = SceneRef->GetRegistry()->GetEntity(Selected);

				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					ImGui::MenuItem("Add Component");

					ImGui::EndPopup();
				}

				ImGui::Text("Selected: %s", Ent->GetEntityFullName().c_str());
				for (Component* Comp : Ent->GetAllComponents())
					Comp->OnImGuiRender();
			}
		}
		else
			ImGui::Text("No entity selected.");
	}
	ImGui::End();
}