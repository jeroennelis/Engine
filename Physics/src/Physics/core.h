#pragma once

#ifdef EN_PLATFORM_WINDOWS
	#ifdef EN_BUILD_DLL
		#define PHYSICS_API __declspec(dllexport)
	#else
		#define PHYSICS_API __declspec(dllimport)
	#endif // PH_BUILD_DLL

#else
	#error Engine only supports Windows!
#endif // PH_PLATFORM_WINDOWS