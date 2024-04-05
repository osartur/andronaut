#if not defined(ANUT_TIMER_H)
#define ANUT_TIMER_H
#include <chrono>

using std::chrono::high_resolution_clock;

class Timer
{
public:
	Timer();
	virtual ~Timer() = default;
	
	void start();
	void pause();
	float restart();
	float elapsed() const;
	bool isPaused() const;
	
private:
	static high_resolution_clock::time_point now();
	
	high_resolution_clock::time_point _start;
	high_resolution_clock::time_point _end;
	bool _paused;
};


inline bool Timer::isPaused() const
{
	return _paused;
}

inline high_resolution_clock::time_point Timer::now()
{
	return high_resolution_clock::now();
}

#endif
