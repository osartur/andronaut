#include "math/timer.h"
#include <cmath>

using std::chrono::duration_cast;
using std::chrono::duration;

Timer::Timer()
{
	m_paused = true;
	m_start = m_end = Now();
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

float Timer::Reset()
{
	high_resolution_clock::duration elapsed;
	if (m_paused)
	{
		elapsed = m_end - m_start;
		m_start = m_end;
	}
	else
	{
		m_end = Now();
		elapsed = m_end - m_start;
		m_start = m_end;
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
