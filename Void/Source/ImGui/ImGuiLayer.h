#pragma once

#include "Void/Layer.h"

#include "Void/Events/ApplicationEvent.h"
#include "Void/Events/KeyboardEvent.h"
#include "Void/Events/MouseEvent.h"



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

	bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
	bool OnMouseMoved(MouseMoveEvent& e);
	bool OnMouseScrolled(MouseScrolledEvent& e);
	bool OnKeyPressed(KeyPressedEvent& e);
	bool OnKeyReleased(KeyReleasedEvent& e);
	bool OnKeyTyped(KeyTypedEvent& e);
	bool OnWindowResized(WindowResizeEvent& e);

	float m_Time;
};