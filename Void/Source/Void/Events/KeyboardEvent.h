#pragma once

#include "Event.h"

#include "sstream"


class VD_API KeyEvent : public Event
{

public:

	inline int GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EEventCategory::Keyboard | EEventCategory::Input);

protected:

	KeyEvent(int KeyCode) : m_KeyCode(KeyCode) {}

	int m_KeyCode;
};


class VD_API KeyPressedEvent : public KeyEvent
{

public:

	KeyPressedEvent(int KeyCode, int RepeatCount) : KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}

	inline int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::KeyPressed)

private:

	int m_RepeatCount;
};

class VD_API KeyReleasedEvent : public KeyEvent
{
	
public:
	
	KeyReleasedEvent(int KeyCode) : KeyEvent(KeyCode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EEventType::KeyReleased)
};