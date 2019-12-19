#pragma once

#include "Event.h"

#include "sstream"


class VD_API MouseMoveEvent : public Event
{

public:

	MouseMoveEvent(float X, float Y) : m_MouseX(X), m_MouseY(Y) {}

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::MouseMoved)
	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::Input)

private:

	float m_MouseX;
	float m_MouseY;
};


class VD_API MouseScrolledEvent : public Event
{

public:

	MouseScrolledEvent(float XOffset, float YOffset) : m_XOffset(XOffset), m_YOffset(YOffset) {}

	inline GetXOffset() const { return m_XOffset; }
	inline GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset;
	}

	EVENT_CLASS_TYPE(EEventType::MouseScrolled)
	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::Input)

private:

	float m_XOffset;
	float m_YOffset;
};


class VD_API MouseButtonEvent : public Event
{

public:

	inline int GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::Input)

protected:
	MouseButtonEvent(int Button) : m_Button(m_Button) {}

	int m_Button;
};

class VD_API MouseButtonPressedEvent : public MouseButtonEvent
{

public:

	MouseButtonPressedEvent(int Button) : MouseButtonEvent(Button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::MouseButtonPressed)
};

class VD_API MouseButtonReleasedEvent : public MouseButtonEvent
{

public:

	MouseButtonReleasedEvent(int Button) : MouseButtonEvent(Button) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::MouseButtonReleased)
};