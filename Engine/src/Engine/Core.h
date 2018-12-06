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

#define BIT(x) (1 << x)

