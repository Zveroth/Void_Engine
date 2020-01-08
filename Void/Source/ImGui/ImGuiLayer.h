#pragma once

#include "Void/Core/Layer.h"



class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMoveEvent;
class MouseScrolledEvent;
class KeyPressedEvent;
class KeyReleasedEvent;
class KeyTypedEvent;
class WindowResizeEvent;


class  ImGuiLayer : public Layer
{

public:

	ImGuiLayer();
	~ImGuiLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	void Begin();
	void End();
};