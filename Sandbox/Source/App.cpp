#include "Void.h"


class Sandbox : public Application
{

public:

	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Application* CreateApplication()
{
	return new Sandbox();
}