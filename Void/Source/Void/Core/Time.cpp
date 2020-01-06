#include "vdpch.h"
#include "Time.h"


std::chrono::time_point<std::chrono::high_resolution_clock> Time::m_TimePoint;

void Time::Init()
{
	m_TimePoint = std::chrono::high_resolution_clock::now();
}

float Time::GetFrameTime()
{
	std::chrono::time_point<std::chrono::high_resolution_clock> MarkTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> FrameTime = MarkTime - m_TimePoint;
	m_TimePoint = MarkTime;

	return FrameTime.count();
}
