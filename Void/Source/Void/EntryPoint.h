#pragma once


#ifdef VD_PLATFORM_WINDOWS

extern Application* CreateApplication();

int main(int argc, char** argv)
{
	Application* App = CreateApplication();
	App->Run();
	delete App;
}

#endif // VD_PLATFORM_WINDOWS
