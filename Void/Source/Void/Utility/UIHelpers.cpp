#include "vdpch.h"
#include "UIHelpers.h"
#include "imgui.h"
#include "imgui_internal.h"



void UIHelpers::EditVec3(const std::string& Label, glm::vec3& Values, float Min, float Max)
{
	ImGui::PushID(Label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 64.0f);
	ImGui::Text(Label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(2.0f, 2.0f));
	
	float LineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	ImVec2 IndicatorSize(LineHeight + 3.0f, LineHeight);

	ImGui::PushStyleColor(ImGuiCol_Button, {0.8f, 0.0f, 0.0f, 1.0f});
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.8f, 0.0f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.0f, 0.0f, 1.0f });
	ImGui::Button("X", IndicatorSize);
	ImGui::SameLine();
	ImGui::DragFloat("##X", &Values.x, 0.1f, Min, Max);
	ImGui::PopItemWidth();
	ImGui::PopStyleColor(3);
	
	ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.6f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.6f, 0.0f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.6f, 0.0f, 1.0f });
	ImGui::SameLine();
	ImGui::Button("Y", IndicatorSize);
	ImGui::SameLine();
	ImGui::DragFloat("##Y", &Values.y, 0.1f, Min, Max);
	ImGui::PopItemWidth();
	ImGui::PopStyleColor(3);

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.8f, 1.0f });
	ImGui::SameLine();
	ImGui::Button("Z", IndicatorSize);
	ImGui::SameLine();
	ImGui::DragFloat("##Z", &Values.z, 0.1f, Min, Max);
	ImGui::PopItemWidth();
	ImGui::PopStyleColor(3);

	ImGui::PopStyleVar();
	ImGui::Columns(1);

	ImGui::PopID();
}