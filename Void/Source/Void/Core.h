#pragma once


#ifdef VD_PLATFORM_WINDOWS
	#ifdef VD_BUILD_DLL
		#define VD_API __declspec(dllexport)
	#else
		#define VD_API __declspec(dllimport)
	#endif // VD_BUILD_DLL

#endif // VD_PLATFORM_WINDOWS
