#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Polaroid {

	class POLAROID_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define PL_CORE_ERROR(...) ::Polaroid::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PL_CORE_WARN(...) ::Polaroid::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PL_CORE_INFO(...) ::Polaroid::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PL_CORE_TRACE(...) ::Polaroid::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PL_CORE_CRITICAL(...) ::Polaroid::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define PL_ERROR(...) ::Polaroid::Log::GetClientLogger()->error(__VA_ARGS__)
#define PL_WARN(...) ::Polaroid::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PL_INFO(...) ::Polaroid::Log::GetClientLogger()->info(__VA_ARGS__)
#define PL_TRACE(...) ::Polaroid::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PL_CRITICAL(...) ::Polaroid::Log::GetClientLogger()->critical(__VA_ARGS__)
