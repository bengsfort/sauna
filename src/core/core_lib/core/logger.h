#pragma once

#include <string>

namespace sauna_core
{

class Logger
{
public:
	static void LogInfo(const std::string message);
	static void LogDebug(const std::string message);
	static void LogWarn(const std::string message);
	static void LogError(const std::string message);
};

}; // namespace sauna_core
