#pragma once


#ifdef VD_PLATFORM_WINDOWS

#ifdef VD_DLL_LINK
	#ifdef VD_BUILD_DLL
		#define VD_API __declspec(dllexport)
	#else
		#define VD_API __declspec(dllimport)
	#endif // VD_BUILD_DLL
#else
	#define VD_API
#endif // VD_DLL_LINK

#endif // VD_PLATFORM_WINDOWS

#ifdef VD_ENABLE_ASSERTS
	#define VD_ASSERT(x, ...) {if(!(x)) { VD_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VD_CORE_ASSERT(x, ...) {if(!(x)) { VD_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VD_ASSERT(x, ...) x
	#define VD_CORE_ASSERT(x, ...) x
#endif // VD_ENABLE_ASSERTS


#define BIT_SHIFT(x) (1 << x)

#define VD_BIND_EVENT_FUN(x) std::bind(&x, this, std::placeholders::_1)