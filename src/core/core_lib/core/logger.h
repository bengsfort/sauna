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
	static void LogInfo(const std::string& message, const Args&... args)
	{
		TraceLog(LOG_INFO, message.c_str(), args...);
	};

	template <typename... Args>
	static void LogDebug(const std::string& message, const Args&... args)
	{
		TraceLog(LOG_DEBUG, message.c_str(), args...);
	};
	
	template <typename... Args>
	static void LogWarn(const std::string& message, const Args&... args)
	{
		TraceLog(LOG_WARNING, message.c_str(), args...);
	};
	
	template <typename... Args>
	static void LogError(const std::string& message, const Args&... args)
	{
		TraceLog(LOG_ERROR, message.c_str(), args...);
	};
};

}; // namespace sauna_core
