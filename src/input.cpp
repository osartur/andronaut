#include <android/input.h>
#include "input.h"

void Input::ProcessTouch(AInputEvent* ev)
{
	int flags = AMotionEvent_getAction(ev);
	int action = flags & AMOTION_EVENT_ACTION_MASK;
	int index = (flags & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
	            >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
	int id = AMotionEvent_getPointerId(ev, index);
	
	event.touch.id = id;
	event.touch.x = AMotionEvent_getX(ev, index);
	event.touch.y = AMotionEvent_getY(ev, index);
	
	switch (action)
	{
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
		case AMOTION_EVENT_ACTION_DOWN:
			event.type = Event::FINGER_DOWN;
			break;
			
		case AMOTION_EVENT_ACTION_MOVE:
			event.type = Event::FINGER_MOTION;
			break;
			
		case AMOTION_EVENT_ACTION_POINTER_UP:
		case AMOTION_EVENT_ACTION_UP:
			event.type = Event::FINGER_UP;
			break;
	}
}

