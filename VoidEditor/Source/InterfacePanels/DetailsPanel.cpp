#include "vdepch.h"
#include "DetailsPanel.h"
#include "Void/ECS/EntityBase.h"
#include "imgui.h"
#include "Void/UI/PanelBuilder.h"

#include "Void/ECS/Components/TransformComponent.h"
#include "Void/ECS/Components/SpriteComponent.h"
#include "Void/ECS/Components/CameraComponent.h"


void DetailsPanel::OnImGuiRender(ControlledPointer<EntityBase>& SelectedEntity)
{
	ImGui::Begin("Details");
	{
		if (SelectedEntity)
		{
			if (m_Scene)
			{
				if (ImGui::BeginPopupContextWindow(0, 1, false))
				{
					ImGui::Text("Add Component:");

					DrawAddComponent<TransformComponent>(SelectedEntity);
					DrawAddComponent<SpriteComponent>(SelectedEntity);
					DrawAddComponent<CameraComponent>(SelectedEntity);

					ImGui::EndPopup();
				}

				ImGui::Text("Selected: %s", SelectedEntity->GetEntityName().c_str());

				VPanelBuilder PanelBuilder;
				DynamicArray<ControlledPointer<ComponentBase>> Components = SelectedEntity->GetComponents();
				for(const ControlledPointer<ComponentBase>& Component : Components)
				{
					bool bOpen = ImGui::TreeNodeEx(Component->GetComponentName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed);

					if (ImGui::BeginPopupContextItem(0))
					{
						if (ImGui::MenuItem("Delete component"))
						{
							SelectedEntity->DeleteComponent(Component);
						}

						ImGui::EndPopup();
					}

					if (bOpen)
					{
						if(Component)
							Component->OnPanelDraw(PanelBuilder);

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

template<typename T>
void DetailsPanel::DrawAddComponent(ControlledPointer<EntityBase>& Entity)
{
	if (ImGui::MenuItem(T::GetComponentNameStatic().c_str()))
		Entity->AddComponent<T>();
}