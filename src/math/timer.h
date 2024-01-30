#if not defined(ANUT_TIMER_H)
#define ANUT_TIMER_H
#include <chrono>

using std::chrono::high_resolution_clock;

class Timer
{
public:
	Timer();
	virtual ~Timer() = default;
	
	void Start();
	void Pause();
	float Reset();
	float Elapsed() const;
	bool Elapsed(float secs) const;
	bool IsPaused() const;
	
private:
	static high_resolution_clock::time_point Now();
	
	high_resolution_clock::time_point m_start;
	high_resolution_clock::time_point m_end;
	bool m_paused;
};


inline bool Timer::IsPaused() const
{
	return m_paused;
}

inline high_resolution_clock::time_point Timer::Now()
{
	return high_resolution_clock::now();
}

#endif
