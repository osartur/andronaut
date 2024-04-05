#if not defined(ANUT_INPUT_H)
#define ANUT_INPUT_H
#include "event.h"

class android_app;
class AInputEvent;

struct Input
{
	Event event;
	
	void processTouch(AInputEvent* ev);
};

#endif
