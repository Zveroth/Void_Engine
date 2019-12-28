#pragma once

#include "Void/Layer.h"



class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMoveEvent;
class MouseScrolledEvent;
class KeyPressedEvent;
class KeyReleasedEvent;
class KeyTypedEvent;
class WindowResizeEvent;


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