#include "vdepch.h"
#include "DetailsPanel.h"
#include "imgui.h"
#include "Void/ECS/ECSRegistry.h"
#include "Void/ClassManagement/ClassRegistry.h"



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
					ImGui::Text("Add Component:");

					for (ClassHandle* Handle : ClassRegistry::GetRegisteredClasses())
					{
						if (ImGui::MenuItem(Handle->GetName().c_str()))
							Ent->AddComponent(Handle->GetTypeID());
					}

					ImGui::EndPopup();
				}

				ImGui::Text("Selected: %s", Ent->GetEntityFullName().c_str());
				for (Component* Comp : Ent->GetAllComponents())
				{
					bool bOpen = ImGui::TreeNodeEx(Comp->GetComponentName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed);

					if (ImGui::BeginPopupContextItem(0))
					{
						if (ImGui::MenuItem("Delete component"))
						{
							Ent->RemoveComponent(*Comp);
							Comp = nullptr;
						}

						ImGui::EndPopup();
					}

					if (bOpen)
					{
						if(Comp)
							Comp->OnImGuiRender();

						ImGui::TreePop();
					}
				}
			}
		}
		else
			ImGui::Text("No entity selected.");
	}
	ImGui::End();
}