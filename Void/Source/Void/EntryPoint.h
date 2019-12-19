#pragma once


#ifdef VD_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	Log::Initialize();
	VD_CORE_ERROR("Ass");
	VD_CLIENT_CRITICAL("Help");

	Application* App = CreateApplication();
	App->Run();
	delete App;
}

#endif // VD_PLATFORM_WINDOWS
