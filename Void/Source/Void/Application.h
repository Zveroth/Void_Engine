#pragma once
#include "Core.h"


class VD_API Application
{

public:

	Application();
	virtual ~Application();

	void Run();
};

Application* CreateApplication();