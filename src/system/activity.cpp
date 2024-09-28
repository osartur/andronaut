#include "system/activity.h"
#include <GLES3/gl32.h>
#include <cstdlib>
#include <cstring>

namespace anut
{
void* saveState(void* data, unsigned sizeInBytes)
{
	void* saved = malloc(sizeInBytes);
	memcpy(saved, data, sizeInBytes);
	return saved;
}

void Activity::onCreate(void* savedState)
{
	
}

void Activity::onStart()
{
	
}

void Activity::onResume()
{
	
}

void Activity::onPause()
{
	
}

void Activity::onStop()
{
	
}

void Activity::onDestroy()
{
	
}

void Activity::onSaveInstanceState(void** savedState)
{
	
}

void Activity::onSurfaceCreated()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void Activity::onSurfaceDestroyed()
{
	
}

void Activity::onSurfaceChanged(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Activity::onProcessApp()
{
	
}

int Activity::onInputEvent(AInputEvent* event)
{
	// return 1 if the event was handled
	return 0;
}

void Activity::onGainedFocus()
{
	
}

void Activity::onLostFocus()
{
	
}
} // anut namespace
