#include "ANUT/input.h"
#include "android_native_app_glue.h"
#include <android/input.h>

Input::Finger Input::fingers[10];

Input::Input()
{
}

Input::~Input()
{
}

int Input::InputProc(android_app* app, AInputEvent* event)
{
	switch (AInputEvent_getType(event))
	{
		case AINPUT_EVENT_TYPE_MOTION:
			HandleMotion(event);
			return 1;
	}
	return 0;
}

void Input::HandleMotion(AInputEvent* event)
{
	int flags = AMotionEvent_getAction(event);
	int action = flags & AMOTION_EVENT_ACTION_MASK;
	int pointer_index = (flags & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
	int finger_id = AMotionEvent_getPointerId(event, pointer_index);
	Finger* f = &fingers[finger_id];
	
	switch (action)
	{
		case AMOTION_EVENT_ACTION_DOWN:
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
			f->down = true;
			f->control = true;
			f->x = AMotionEvent_getX(event, pointer_index);
			f->y = AMotionEvent_getY(event, pointer_index);
			break;
			
		case AMOTION_EVENT_ACTION_MOVE:
			f->x = AMotionEvent_getX(event, pointer_index);
			f->y = AMotionEvent_getY(event, pointer_index);
			break;
			
		case AMOTION_EVENT_ACTION_UP:
		case AMOTION_EVENT_ACTION_POINTER_UP:
			f->down = false;
			f->control = false;
			break;
	}
}

