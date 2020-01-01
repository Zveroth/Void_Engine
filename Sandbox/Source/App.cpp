#include "Void.h"


class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer") {}

	virtual void OnUpdate() override
	{
		
	}

	virtual void OnImGuiRender() override
	{
		
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
	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}