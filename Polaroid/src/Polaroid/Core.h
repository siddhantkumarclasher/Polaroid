#pragma once	

#ifdef PL_PLATFORM_WINDOWS
	#ifdef PL_BUILD_DLL
		#define POLAROID_API __declspec(dllexport)
	#else
		#define POLAROID_API __declspec(dllimport)
	#endif
#else
	#error Polaroid only supports Windows!
#endif

#ifdef PL_DEBUG
#define PL_ENABLE_ASSETS
#endif

#ifdef PL_ENABLE_ASSETS
#define PL_ASSERT(x, ...) { if(!(x)) { PL_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define PL_CORE_ASSERT(x, ...) { if(!(x)) { PL_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define PL_ASSERT(x, ...)
#define PL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PL_BIND_EVENT_FN(Fn) std::bind(&Fn, this, std::placeholders::_1)