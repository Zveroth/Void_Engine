#pragma once

#include "Void/Core/Layer.h"



#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/KeyboardEvent.h"
#include "Void/Events/MouseEvent.h"


class  ImGuiLayer : public Layer
{

public:

	ImGuiLayer() : Layer("ImGuiLayer") {}

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnEvent(Event& e) override;

	void SetConsumeEvents(bool Consume) { m_bConsumeEvents = Consume; }

	void Begin();
	void End();

	void SetDarkThemeColors();

private:

	bool m_bConsumeEvents = true;
};