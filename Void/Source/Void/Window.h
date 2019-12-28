#pragma once

#include "vdpch.h"

#include "Void/Core.h"
#include "Void/Events/Event.h"

struct WindowProperties
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProperties(const std::string& title = "Void Enigne", unsigned int width = 1280, unsigned int height = 720)
		: Title(title), Width(width), Height(height) {}
};


class VD_API Window
{

public:

	virtual ~Window() {}

	virtual void OnUpdate() = 0;

	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;

	virtual void SetEventCallback(const std::function<void(Event&)>& Callback) = 0;
	virtual void SetVSync(bool bEnabled) = 0;
	virtual bool IsVSyncEnabled() const = 0;

	virtual void* GetNativeWindow() const = 0;

	static Window* Create(const WindowProperties& Properties = WindowProperties());
};