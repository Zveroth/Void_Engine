#include "Void.h"
#include "Void/EntryPoint.h"

#include "SandboxLayer.h"



class Sandbox : public Application
{

public:

	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}