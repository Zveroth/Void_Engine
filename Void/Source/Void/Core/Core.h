#pragma once

#include "memory"

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
	#define VD_ASSERT(x, ...) {if(!(x)) { VD_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VD_CORE_ASSERT(x, ...) {if(!(x)) { VD_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VD_CORE_ASSERT_CUSTOM(x, m) {if(!(x)) { m; __debugbreak(); } }
#else
	#define VD_ASSERT(x, ...)
	#define VD_CORE_ASSERT(x, ...)
	#define VD_CORE_ASSERT_CUSTOM(x, m)
#endif // VD_ENABLE_ASSERTS

#include "Void/Containers/DynamicArray.h"

#define INDEX_NONE -1

#define BIT_SHIFT(x) (1 << x)

#define VD_BIND_EVENT_FUN(x) [this](auto&&... args) -> decltype(auto) { return this->x(std::forward<decltype(args)>(args)...); }


template <typename T>
using Ref = std::shared_ptr<T>;
#define CreateRef std::make_shared

template <typename T>
using UniqueRef = std::unique_ptr<T>;
#define CreateUnique std::make_unique

template <typename T>
using WeakRef = std::weak_ptr<T>;

typedef size_t type_id;