#include "Void.h"

#include "imgui.h"

class ExmpLayer : public Layer
{

public:

	ExmpLayer() : Layer("ExampleLayer") {}

	virtual void OnUpdate() override
	{
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Some random window");
		ImGui::Text("A window");
		ImGui::End();
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