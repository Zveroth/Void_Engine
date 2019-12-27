#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



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



//#ifdef VD_BUILD_DLL
#define A 1
#ifdef A

#define VD_CORE_TRACE(...)		Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VD_CORE_INFO(...)		Log::GetCoreLogger()->info(__VA_ARGS__)
#define VD_CORE_WARNING(...)	Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VD_CORE_ERROR(...)		Log::GetCoreLogger()->error(__VA_ARGS__)
#define VD_CORE_CRITICAL(...)	Log::GetCoreLogger()->critical(__VA_ARGS__)

#define VD_TRACE(...)			Log::GetClientLogger()->trace(__VA_ARGS__)
#define VD_INFO(...)			Log::GetClientLogger()->info(__VA_ARGS__)
#define VD_WARNING(...)			Log::GetClientLogger()->warn(__VA_ARGS__)
#define VD_ERROR(...)			Log::GetClientLogger()->error(__VA_ARGS__)
#define VD_CRITICAL(...)		Log::GetClientLogger()->critical(__VA_ARGS__)

#else

#define VD_CORE_TRACE(...)
#define VD_CORE_INFO(...)
#define VD_CORE_WARNING(...)
#define VD_CORE_ERROR(...)
#define VD_CORE_CRITICAL(...)

#define VD_TRACE(...)
#define VD_INFO(...)
#define VD_WARNING(...)
#define VD_ERROR(...)
#define VD_CRITICAL(...)

#endif // VD_BUILD_DLL