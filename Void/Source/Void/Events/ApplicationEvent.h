#pragma once

#include "Event.h"


class VD_API WindowResizeEvent : public Event
{

public:

	WindowResizeEvent(unsigned int Width, unsigned int Height) : m_Width(Width), m_Height(Height) {}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::WindowResize)
	EVENT_CLASS_CATEGORY(EEventCategory::App)

private:

	unsigned int m_Width;
	unsigned int m_Height;
};


class VD_API WindowCloseEvent : public Event
{

public:

	WindowCloseEvent() {}

	EVENT_CLASS_TYPE(EEventType::WindowClose)
	EVENT_CLASS_CATEGORY(EEventCategory::App)
};