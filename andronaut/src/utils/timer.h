#if not defined(ANUT_TIMER_H)
#define ANUT_TIMER_H
#include <chrono>

namespace anut
{
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
	static std::chrono::high_resolution_clock::time_point now();
	
	std::chrono::high_resolution_clock::time_point _start;
	std::chrono::high_resolution_clock::time_point _end;
	bool _paused;
};


inline bool Timer::isPaused() const
{
	return _paused;
}

inline std::chrono::high_resolution_clock::time_point Timer::now()
{
	return std::chrono::high_resolution_clock::now();
}
} // anut namespace

#endif
