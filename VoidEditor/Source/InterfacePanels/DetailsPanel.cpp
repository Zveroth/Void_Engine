#include "vdepch.h"
#include "DetailsPanel.h"
#include "Void/ECS/EntityBase.h"
#include "imgui.h"
#include "Void/UI/PanelBuilder.h"



void DetailsPanel::OnImGuiRender(EntityBase* SelectedEntity)
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

					ImGui::EndPopup();
				}

				ImGui::Text("Selected: %s", SelectedEntity->GetEntityName().c_str());

				VPanelBuilder PanelBuilder;
				for (ComponentBase* Comp : SelectedEntity->GetComponents())
				{
					bool bOpen = ImGui::TreeNodeEx(Comp->GetComponentName().c_str(), ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed);

					if (ImGui::BeginPopupContextItem(0))
					{
						if (ImGui::MenuItem("Delete component"))
						{
							SelectedEntity->DeleteComponent(Comp);
							Comp = nullptr;
						}

						ImGui::EndPopup();
					}

					if (bOpen)
					{
						if(Comp)
							Comp->OnPanelDraw(PanelBuilder);

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