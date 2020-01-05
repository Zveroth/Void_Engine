#pragma once

#include "chrono"



class Time
{

public:

	Time() {}

	void Init();

	float GetFrameTime();

private:

	std::chrono::time_point<std::chrono::high_resolution_clock> m_TimePoint;
};