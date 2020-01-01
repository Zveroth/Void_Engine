#pragma once

#include "Event.h"


class  MouseMoveEvent : public Event
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
	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::InputEvent)

private:

	float m_MouseX;
	float m_MouseY;
};


class  MouseScrolledEvent : public Event
{

public:

	MouseScrolledEvent(float XOffset, float YOffset) : m_XOffset(XOffset), m_YOffset(YOffset) {}

	inline float GetXOffset() const { return m_XOffset; }
	inline float GetYOffset() const { return m_YOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::MouseScrolled)
	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::InputEvent)

private:

	float m_XOffset;
	float m_YOffset;
};


class  MouseButtonEvent : public Event
{

public:

	inline int GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EEventCategory::Mouse | EEventCategory::InputEvent)

protected:
	MouseButtonEvent(int Button) : m_Button(Button) {}

	int m_Button;
};

class  MouseButtonPressedEvent : public MouseButtonEvent
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

class  MouseButtonReleasedEvent : public MouseButtonEvent
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