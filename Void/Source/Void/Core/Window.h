#pragma once

#include "vdpch.h"

#include "Void/Core/Core.h"
#include "Void/Events/Event.h"

struct WindowProperties
{
	std::string Title;
	uint32_t Width;
	uint32_t Height;

	WindowProperties(const std::string& title = "Void Enigne", uint32_t width = 1280, uint32_t height = 720)
		: Title(title), Width(width), Height(height) {}
};


class  Window
{

public:

	virtual ~Window() {}

	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual void SetEventCallback(const std::function<void(Event&)>& Callback) = 0;
	virtual void SetVSync(bool bEnabled) = 0;
	virtual bool IsVSyncEnabled() const = 0;

	virtual void* GetNativeWindow() const = 0;

	static Window* Create(const WindowProperties& Properties = WindowProperties());
};