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

Timer::TimePoint Timer::now()
{
	return Clock::now();
}

float Timer::timeSince(const TimePoint& markTime)
{
	auto elapsed = now() - markTime;
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::timeSince(const TimePoint& pointA, const TimePoint& pointB)
{
	auto elapsed = pointB - pointA;
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::start()
{
	TimePoint rightNow = now();
	decltype(_pausePoint - _startPoint) deltaTime;
	if (_paused)
	{
		deltaTime = _pausePoint - _startPoint;
		_startPoint = rightNow - deltaTime;
		_paused = false;
	}
	else
	{
		deltaTime = rightNow - _startPoint;
		_startPoint = rightNow;
	}
	return duration_cast<duration<float>>(deltaTime).count();
}

void Timer::pause()
{
	_pausePoint = now();
	_paused = true;
}

float Timer::elapsed() const
{
	TimePoint mark = _paused ? _pausePoint : now();
	return timeSince(_startPoint, mark);
}
} // anut namespace
