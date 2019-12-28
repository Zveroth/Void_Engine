#include "Void.h"


class Sandbox : public Application
{

public:

	Sandbox()
	{
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