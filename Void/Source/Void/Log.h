#pragma once

#include "memory"

#include "Core.h"
#include "spdlog/spdlog.h"



class VD_API Log
{

public:
	
	static void Initialize();

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_CoreLogger; }
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

private:

	static std::shared_ptr<spdlog::logger> m_CoreLogger;
	static std::shared_ptr<spdlog::logger> m_ClientLogger;
};


#define A 1
#ifdef A

#define VD_CORE_INFO(...)		Log::GetCoreLogger()->info(__VA_ARGS__)
#define VD_CORE_WARNING(...)	Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VD_CORE_ERROR(...)		Log::GetCoreLogger()->error(__VA_ARGS__)
#define VD_CORE_CRITICAL(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)

#define VD_CLIENT_INFO(...)		Log::GetClientLogger()->info(__VA_ARGS__)
#define VD_CLIENT_WARNING(...)	Log::GetClientLogger()->warn(__VA_ARGS__)
#define VD_CLIENT_ERROR(...)	Log::GetClientLogger()->error(__VA_ARGS__)
#define VD_CLIENT_CRITICAL(...)	Log::GetClientLogger()->critical(__VA_ARGS__)

#else

#define VD_CORE_INFO(...)
#define VD_CORE_WARNING(...)
#define VD_CORE_ERROR(...)
#define VD_CORE_CRITICAL(...)

#define VD_CLIENT_INFO(...)
#define VD_CLIENT_WARNING(...)
#define VD_CLIENT_ERROR(...)
#define VD_CLIENT_CRITICAL(...)

#endif // 1