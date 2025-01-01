#pragma once

#include <string>
#include <format>

#include "raylib.h"

namespace sauna_core
{

class Logger
{
public:
	static void Init();
	static void Shutdown();
	static void SetLogLevel(int level);

	template <typename... Args>
	static void LogInfo(const std::format_string<Args...> message, Args&&... args)
	{
		auto formatted = std::format(message, std::forward<Args>(args)...);
		TraceLog(LOG_INFO, formatted.c_str());
	};

	template <typename... Args>
	static void LogDebug(const std::format_string<Args...> message, Args&&... args)
	{
		auto formatted = std::format(message, std::forward<Args>(args)...);
		TraceLog(LOG_DEBUG, formatted.c_str());
	};
	
	template <typename... Args>
	static void LogWarn(const std::format_string<Args...> message, Args&&... args)
	{
		auto formatted = std::format(message, std::forward<Args>(args)...);
		TraceLog(LOG_WARNING, formatted.c_str());
	};
	
	template <typename... Args>
	static void LogError(const std::format_string<Args...> message, Args&&... args)
	{
		auto formatted = std::format(message, std::forward<Args>(args)...);
		TraceLog(LOG_ERROR, formatted.c_str());
	};
};

}; // namespace sauna_core
