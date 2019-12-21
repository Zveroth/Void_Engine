#include "vdpch.h"

#include "Log.h"

#include"spdlog/sinks/stdout_color_sinks.h"



std::shared_ptr<spdlog::logger> Log::m_CoreLogger;
std::shared_ptr<spdlog::logger> Log::m_ClientLogger;

void Log::Initialize()
{
	spdlog::set_pattern("%^[%n::%l | %T]: %v%$");

	m_CoreLogger = spdlog::stdout_color_mt("VOID");
	m_CoreLogger->set_level(spdlog::level::trace);

	m_ClientLogger = spdlog::stdout_color_mt("APP");
	m_CoreLogger->set_level(spdlog::level::trace);
}