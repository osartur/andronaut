#include "system/timer.h"
#include <cmath>

using std::chrono::duration_cast;
using std::chrono::duration;

namespace anut
{
Timer::Timer()
{
	_paused = false;
	start();
}

Timer::TimePoint Timer::getCurrentTimePoint()
{
	return Clock::now();
}

float Timer::getTimeSince(const TimePoint& markTime)
{
	auto elapsed = getCurrentTimePoint() - markTime;
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::getTimeSince(const TimePoint& pointA, const TimePoint& pointB)
{
	auto elapsed = pointB - pointA;
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::start()
{
	TimePoint rightnow = getCurrentTimePoint();
	decltype(_pausePoint - _startPoint) deltaTime;
	if (_paused)
	{
		deltaTime = _pausePoint - _startPoint;
		_startPoint = rightnow - deltaTime;
		_paused = false;
	}
	else
	{
		deltaTime = rightnow - _startPoint;
		_startPoint = rightnow;
	}
	return duration_cast<duration<float>>(deltaTime).count();
}

void Timer::pause()
{
	_pausePoint = getCurrentTimePoint();
	_paused = true;
}

float Timer::getElapsedTime() const
{
	TimePoint mark = _paused ? _pausePoint : getCurrentTimePoint();
	return getTimeSince(_startPoint, mark);
}
} // anut namespace
