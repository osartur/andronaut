#include "utils/timer.h"
#include <cmath>

using std::chrono::duration_cast;
using std::chrono::duration;

Timer::Timer()
{
	m_paused = false;
	Start();
}

void Timer::Start()
{
	if (m_paused)
	{
		auto elapsed = m_end - m_start;
		m_start = Now() - elapsed;
		m_paused = false;
	}
	else
	{
		m_start = Now();
	}
}

void Timer::Pause()
{
	if (!m_paused)
	{
		m_end = Now();
		m_paused = true;
	}
}

float Timer::Restart()
{
	high_resolution_clock::duration elapsed;
	if (m_paused)
	{
		elapsed = m_end - m_start;
		m_start = Now() - elapsed;
		m_paused = false;
	}
	else
	{
		auto now = Now();
		elapsed = now - m_start;
		m_start = now;
	}
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::Elapsed() const
{
	auto end = m_paused ? m_end : Now();
	auto elapsed = duration_cast<duration<float>>(end - m_start);
	return elapsed.count();
}

bool Timer::Elapsed(float secs) const
{
	float elapsed = Elapsed();
	return abs(elapsed - secs) < 0.000001f || elapsed > secs;
}
