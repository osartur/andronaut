#include "activity.h"
#include "window.h"
#include <GLES3/gl32.h>

Window* Activity::window = nullptr;
Engine* Activity::engine = nullptr;

void Activity::OnCreate(void* saved_state)
{
	
}

void Activity::OnStart()
{
	
}

void Activity::OnResume()
{
	
}

void Activity::OnPause()
{
	
}

void Activity::OnStop()
{
	
}

void Activity::OnDestroy()
{
	
}

void Activity::OnSaveInstanceState(void** saved_state)
{
	
}

void Activity::OnSurfaceCreated()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void Activity::OnSurfaceChanged(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Activity::OnUpdate(const Event& event, float dt)
{
	
}

void Activity::OnDrawFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Activity::OnGainedFocus()
{
	
}

void Activity::OnLostFocus()
{
	
}

