#pragma once

#ifdef EN_PLATFORM_WINDOWS
	#ifdef EN_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // ENGINE_BUILD_DLL

#else
	#error Engine only supports Windows!
#endif // ENGINE_PLATFORM_WINDOWS

#ifdef  EN_ENABLE_ASSERTS
	#define EN_ASSERT(x, ...) { if(!(x)) {EN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EN_CORE_ASSERT(x, ...) { if(!(x)) {EN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define EN_ASSERT(x, ...)
	#define EN_CORE_ASSERT(x, ...)
#endif //  EN_ENABLE_ASSERTS


#define BIT(x) (1 << x)

