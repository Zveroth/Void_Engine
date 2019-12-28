#pragma once

#include "Void/Layer.h"


class VD_API ImGuiLayer : public Layer
{

public:

	ImGuiLayer();
	~ImGuiLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent(Event& e) override;

private:

	float m_Time;
};