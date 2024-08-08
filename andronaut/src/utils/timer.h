#if not defined(ANUT_TIMER_H)
#define ANUT_TIMER_H
#include <chrono>

namespace anut
{
class Timer
{
public:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	
	static TimePoint now();
	static float timeSince(const TimePoint& markTime);
	static float timeSince(const TimePoint& pointA, const TimePoint& pointB);
	
	Timer();
	virtual ~Timer() = default;
	
	float start();
	float restart(); // Wrap function for start()
	void pause();
	float elapsed() const;
	bool isPaused() const;
	
private:
	TimePoint _startPoint;
	TimePoint _pausePoint;
	bool _paused;
};


inline float Timer::restart()
{
	return start();
}

inline bool Timer::isPaused() const
{
	return _paused;
}
} // anut namespace

#endif
