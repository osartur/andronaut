#if not defined(ANUT_EVENT_H)
#define ANUT_EVENT_H

class AInputEvent;

namespace anut
{
struct MotionEvent
{
	enum { ACTION_DOWN = 0, ACTION_MOVE, ACTION_UP };
	
	MotionEvent(const AInputEvent* ev);
	
	int action;
	int id;
	float x;
	float y;
};
}

#endif
