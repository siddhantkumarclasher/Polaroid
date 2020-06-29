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