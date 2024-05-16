#include "utils/timer.h"
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

void Timer::start()
{
	if (_paused)
	{
		auto elapsed = _end - _start;
		_start = now() - elapsed;
		_paused = false;
	}
	else
	{
		_start = now();
	}
}

void Timer::pause()
{
	if (!_paused)
	{
		_end = now();
		_paused = true;
	}
}

float Timer::restart()
{
	std::chrono::high_resolution_clock::duration elapsed;
	if (_paused)
	{
		elapsed = _end - _start;
		_start = now() - elapsed;
		_paused = false;
	}
	else
	{
		auto right_now = now();
		elapsed = right_now - _start;
		_start = right_now;
	}
	return duration_cast<duration<float>>(elapsed).count();
}

float Timer::elapsed() const
{
	auto end = _paused ? _end : now();
	auto elapsed = duration_cast<duration<float>>(end - _start);
	return elapsed.count();
}
} // anut namespace
