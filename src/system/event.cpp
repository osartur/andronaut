#include "system/event.h"
#include <android/input.h>

namespace anut
{
MotionEvent::MotionEvent(const AInputEvent* ev)
{
	int flags = AMotionEvent_getAction(ev);
	int index = (flags & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
	             >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
	
	id = AMotionEvent_getPointerId(ev, index);
	x = AMotionEvent_getX(ev, index);
	y = AMotionEvent_getY(ev, index);
	
	switch (flags & AMOTION_EVENT_ACTION_MASK)
	{
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
		case AMOTION_EVENT_ACTION_DOWN:
			action = ACTION_DOWN;
			break;
			
		case AMOTION_EVENT_ACTION_MOVE:
			action = ACTION_MOVE;
			break;
			
		case AMOTION_EVENT_ACTION_POINTER_UP:
		case AMOTION_EVENT_ACTION_UP:
			action = ACTION_UP;
			break;
	}
}
} // anut namespace
