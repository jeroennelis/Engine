#pragma once

#ifdef EN_PLATFORM_WINDOWS
#if EN_DYNAMIC_LINK
	#ifdef EN_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif // ENGINE_BUILD_DLL
#else
	#define ENGINE_API 
#endif
#else
	#error Engine only supports Windows!
#endif // ENGINE_PLATFORM_WINDOWS

#ifdef  EN_ENABLE_ASSERTS
	#define EN_ASSERT(x, ...) { if(!(x)) {EN_ERROR( Assertion Failed: {0} , __VA_ARGS__); __debugbreak(); } }
	#define EN_CORE_ASSERT(x, ...) { if(!(x)) {EN_CORE_ERROR( Assertion Failed: {0} , __VA_ARGS__); __debugbreak(); } }
#else
	#define EN_ASSERT(x, ...)
	#define EN_CORE_ASSERT(x, ...)
#endif //  EN_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define EN_BIND_EVENT_FN(fn) std::bind(&fn,this, std::placeholders::_1)

#define GLM_ENABLE_EXPERIMENTAL

