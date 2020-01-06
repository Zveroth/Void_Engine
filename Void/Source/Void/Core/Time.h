#pragma once

#include "chrono"



class Time
{

public:

	Time() {}

	static void Init();

	static float GetFrameTime();

private:

	static std::chrono::time_point<std::chrono::high_resolution_clock> m_TimePoint;
};