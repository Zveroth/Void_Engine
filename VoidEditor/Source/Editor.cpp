#include "vdepch.h"
#include "Void.h"
#include "Void/EntryPoint.h"

#include "EditorLayer.h"

class Editor : public Application
{

public:

	Editor() : Application("Void Editor")
	{
		PushLayer(new EditorLayer());
	}

	~Editor()
	{

	}
};

Application* CreateApplication()
{
	return new Editor();
}