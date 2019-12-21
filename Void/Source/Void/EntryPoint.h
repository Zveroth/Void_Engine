#pragma once


#ifdef VD_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	Log::Initialize();
	VD_CORE_INFO("Core log working");
	VD_INFO("Client log working");

	Application* App = CreateApplication();
	App->Run();
	delete App;
}

#endif // VD_PLATFORM_WINDOWS
