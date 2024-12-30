#pragma once

#include <chrono>

namespace sauna_chrono
{

using namespace std;

// Measures time between two points in code in seconds.
// Intended to be used in situations where you want to measure the time it takes
// to execute a block of code, outside of 'frame time' measuring (which is done
// via the sauna_chrono::Clock class and only updates each frame).
//
// The timer starts when the Measure object is created and stops when the done()
// is called, which determines the duration of the measured time. Once done() is
// called, you cannot restart or stop the timer again.
//
// NOTE: The duration is stored as a double, which represents seconds. This allows
// for sub-second precision which allows us to measure more precise timings.
class Measure
{
public:
    Measure()
    {
        m_isDone = false;
        m_start = chrono::steady_clock::now();
        m_duration = chrono::duration<double>::zero();
    }

    ~Measure() = default;

    inline void done()
    {
        if (m_isDone) return;

        m_isDone = true;
        const auto end = chrono::steady_clock::now();
        m_duration = end - m_start;
    }

    double getDurationSeconds() const { return m_duration.count(); }
    double getDurationMilliseconds() const { return m_duration.count() * 1000.0; }
    bool isRunning() const { return !m_isDone; }

private:
    chrono::steady_clock::time_point m_start;
    chrono::duration<double> m_duration;
    bool m_isDone;
};

}; // namespace sauna_chrono
