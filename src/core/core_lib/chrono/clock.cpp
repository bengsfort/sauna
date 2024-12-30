#include "core_lib/chrono/clock.h"

using namespace sauna_chrono;

double Clock::s_lastTickTime = 0.0;
int Clock::s_tickCount = 0;
double Clock::s_deltaTime = 0.0;
double Clock::s_totalTime = 0.0;
bool Clock::s_isRunning = false;
double Clock::s_updateTime = 0.0;
double Clock::s_drawTime = 0.0;
FrameDiagnosticManager Clock::s_diagnostics = {};

void Clock::Init()
{
    s_tickCount = 0;
    s_deltaTime = 0.0;
    s_totalTime = 0.0;
    s_isRunning = true;
    s_lastTickTime = GetTime();
    s_diagnostics.flush();
}

void Clock::Shutdown()
{
    Clock::Tick();
    s_isRunning = false;
    s_diagnostics.flush();
}

void Clock::Tick()
{
    if (!s_isRunning) return;

    const auto now = GetTime();

    s_tickCount++;
    s_deltaTime = now - s_lastTickTime;
    s_totalTime += s_deltaTime;
    s_lastTickTime = now;

    s_diagnostics.pushFrame(s_deltaTime);
}

void Clock::MarkDrawDone()
{
    auto now = GetTime();
    // NOTE: This occurs AFTER update, so we can safely determine the draw time based on now - updateTime.
    s_drawTime = now - s_updateTime;
}

void Clock::MarkUpdateDone()
{
    auto now = GetTime();
    // NOTE: This occurs directly after the frame tick, so we can safely determine the draw time based on now - lastTickTime.
    s_updateTime = now - s_lastTickTime;
}