#include "raylib.h"
#include "core_lib/core/logger.h"

using namespace sauna_core;

// TODO: This should open up a file to log to, and redirect logs to there.
// IF it is a dev environment, also log to console.
void Logger::Init()
{
	// TODO: Implement. Open file for logging.
	// TODO: Set TraceLog to write to open file and conditionally to console.
}

void Logger::Shutdown()
{
	// TODO: Implement. Close file for logging.
}

void Logger::SetLogLevel(int level)
{
	SetTraceLogLevel(level);
}

void Logger::LogInfo(const std::string message)
{
	TraceLog(LOG_INFO, message.c_str());
}

void Logger::LogDebug(const std::string message)
{
	TraceLog(LOG_DEBUG, message.c_str());
}

void Logger::LogWarn(const std::string message)
{
	TraceLog(LOG_WARNING, message.c_str());
}

void Logger::LogError(const std::string message)
{
	TraceLog(LOG_ERROR, message.c_str());
}
