#include "Void.h"


class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer") {}

	virtual void OnUpdate() override
	{
		if (Input::IsKeyPressed(VD_KEY_W))
			VD_TRACE("Pressed");
	}

	virtual void OnEvent(Event& e) override
	{

	}
};

class Sandbox : public Application
{

public:

	Sandbox()
	{
		PushLayer(new ExmpLayer());
		PushOverlay(new ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}