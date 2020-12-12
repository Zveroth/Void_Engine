#pragma once

#include "Void/Core/Core.h"


enum class EEventType : unsigned int
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowsLostFocus, WindowMoved,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EEventCategory
{
	None = 0,
	App = BIT_SHIFT(0),
	InputEvent = BIT_SHIFT(1),
	Keyboard = BIT_SHIFT(2),
	Mouse = BIT_SHIFT(3),
	MouseButton = BIT_SHIFT(4)
};


#define EVENT_CLASS_TYPE(Type)	static EEventType GetStaticType() { return Type; }\
								virtual EEventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #Type; }

#define  EVENT_CLASS_CATEGORY(Category) virtual int GetCategoryFlags() const override { return Category; }


class  Event
{
	friend class EvenDispatcher;

public:

	virtual ~Event() = default;

	virtual EEventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EEventCategory Category)
	{
		return (GetCategoryFlags() & Category);
	}

	bool m_bHandled = false;
};


class EventDispatcher
{

public:

	EventDispatcher(Event& DispatchedEvent) : m_Event(DispatchedEvent) {}

	template <typename T>
	bool Dispatch(std::function<bool(T&)> FunctionRef)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_bHandled = FunctionRef(*(T*)&m_Event);
			return true;
		}
		return false;
	}

private:

	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}