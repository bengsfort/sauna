#pragma once

#include "raylib.h"

namespace sauna_chrono
{

const static int k_DiagnosticBufferSize = 100;

struct FrameDiagnostics
{
    int frameCount;
    double averageFrameTime;
    double maxFrameTime;
    double minFrameTime;
};

// Container for frame timing related diagnostics.
// Maintains a buffer of frame times for the last 100 frames, and calculates
// the average, min, and max frame times for the current buffer, allowing for a
// more detailed view of the frame time performance.
class FrameDiagnosticManager
{
private:
    double m_frameTimes[k_DiagnosticBufferSize];
    int m_cursor = 0;
    FrameDiagnostics m_diagnostics = { 0 };

public:
    inline void pushFrame(double frameTime)
    {
        if (m_diagnostics.frameCount < k_DiagnosticBufferSize)
            m_diagnostics.frameCount++;

        m_frameTimes[m_cursor] = frameTime;
        m_cursor = (m_cursor + 1) % k_DiagnosticBufferSize;

        if (frameTime > m_diagnostics.maxFrameTime) m_diagnostics.maxFrameTime = frameTime;
        if (frameTime < m_diagnostics.minFrameTime) m_diagnostics.minFrameTime = frameTime;

        double sum = 0.0f;
        for (int i = 0; i < m_diagnostics.frameCount; i++)
            sum += m_frameTimes[i];
        
        if (m_diagnostics.frameCount > 0) m_diagnostics.averageFrameTime = sum / m_diagnostics.frameCount;
    };

    inline void flush()
    {
        m_diagnostics.frameCount = 0;
        m_cursor = 0;
        m_diagnostics.averageFrameTime = 0.0f;
        m_diagnostics.minFrameTime = 0.0f;
        m_diagnostics.maxFrameTime = 0.0f;

        for (int i = 0; i < k_DiagnosticBufferSize; i++) {
            m_frameTimes[i] = 0.0;
        }
    }

    inline double getAverageFrameTime() const { return m_diagnostics.averageFrameTime; }
    inline double getMinFrameTime() const { return m_diagnostics.minFrameTime; }
    inline double getMaxFrameTime() const { return m_diagnostics.maxFrameTime; }
    inline int sampleCount() const { return m_diagnostics.frameCount; }
    inline FrameDiagnostics &getFrameDiagnostics() { return m_diagnostics; }
};

// Static Clock class for keeping time.
//
// This class is intended to be used for keeping track of the current game-relative
// time. It measures the time taken between each frame, ie, the time between each
// call to Tick(). This means that every component, system, or actor updating can
// calculate their state based on the same current time value for consistency.
//
// Clock tracks the time in seconds as a double, allowing sub-second precision and
// conversion to milliseconds if needed.
//
// Can be reset via subsequent calls to Clock::Init().
class Clock
{
// TODO: Right now you can abuse the mark system; need to add bool flags to prevent multiple calls to MarkUpdateDone or MarkDrawDone.
protected:
    static double s_lastTickTime;
    static double s_updateTime;
    static double s_drawTime;
    static int s_tickCount;
    static double s_deltaTime;
    static double s_totalTime;
    static bool s_isRunning;
    static FrameDiagnosticManager s_diagnostics;

public:
    static void Init();
    static void Shutdown();
    static void Tick();
    static void MarkUpdateDone();
    static void MarkDrawDone();

    inline static const double GetUpdateTime() { return s_updateTime; }
    inline static const double GetDrawTime() { return s_drawTime; }
    inline static const double GetFrameDeltaTime() { return s_deltaTime; }
    inline static const double GetTotalTime() { return s_totalTime; }
    inline static const int GetTickCount() { return s_tickCount; }
    inline static const double GetAverageFrameTime() { return s_diagnostics.getAverageFrameTime(); }
    inline static const double GetMinFrameTime() { return s_diagnostics.getMinFrameTime(); }
    inline static const double GetMaxFrameTime() { return s_diagnostics.getMaxFrameTime(); }
    inline static const int GetFrameSampleCount() { return s_diagnostics.sampleCount(); }
    inline static FrameDiagnostics &GetFrameDiagnostics() { return s_diagnostics.getFrameDiagnostics(); }
};

}; // namespace sauna_chrono