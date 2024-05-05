#include <GLES3/gl32.h>
#include <cstdlib>
#include <cstring>
#include "activity.h"
#include "engine.h"
#include "window.h"
#include "event.h"

Window* Activity::window = nullptr;
Engine* Activity::engine = nullptr;

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

void Activity::onDrawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Activity::onTouchEvent(const MotionEvent& event)
{
	
}

void Activity::onGainedFocus()
{
	
}

void Activity::onLostFocus()
{
	
}

