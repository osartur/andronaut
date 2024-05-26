#include <android/native_activity.h>
#include <android/window.h>
#include <android/input.h>
#include "android_native_app_glue.h"
#include "activity.h"
#include "engine.h"
#include "window.h"

namespace anut
{
Window* Engine::window = nullptr;
android_app* Engine::state = nullptr;
int Engine::loopState = STOPPED;
int Engine::exitCode = 0;

Engine::Engine(android_app* app)
{
	window = new Window;
	state = app;
	state->userData = this;
	state->onAppCmd = activityCall;
	state->onInputEvent = inputCall;
}

Engine::~Engine()
{
	delete window;
}

int Engine::run(Activity* activity)
{
	_userActivity = activity;
	_userActivity->onCreate(state->savedState);
	loopState = STOPPED;
	
	while (true)
	{
		android_poll_source* source = nullptr;
		int fd, event;
		while (ALooper_pollOnce(loopState, &fd, &event, (void**) &source) >= 0)
		{
			if (source != nullptr)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				return exitCode;
			}
		}
		_userActivity->onUpdate();
	}
}

void Engine::finish(int status)
{
	ANativeActivity_finish(state->activity);
	loopState = STOPPED;
	exitCode = status;
}

void Engine::activityProc(int cmd)
{
	switch (cmd)
	{
		case APP_CMD_START:
			_userActivity->onStart();
			break;
			
		case APP_CMD_RESUME:
			_userActivity->onResume();
			break;
			
		case APP_CMD_INIT_WINDOW:
			if (!window->init(state->window, state->activity))
			{
				finish(-1);
				break;
			}
			_userActivity->onSurfaceCreated();
			_userActivity->onSurfaceChanged(window->width(), window->height());
			loopState = RUNNING;
			break;
			
		case APP_CMD_GAINED_FOCUS:
			_userActivity->onGainedFocus();
			break;
			
		case APP_CMD_PAUSE:
			_userActivity->onPause();
			break;
			
		case APP_CMD_LOST_FOCUS:
			_userActivity->onLostFocus();
			break;
			
		case APP_CMD_STOP:
			_userActivity->onStop();
			break;
			
		case APP_CMD_TERM_WINDOW:
			window->destroy();
			_userActivity->onSurfaceDestroyed();
			loopState = STOPPED;
			break;
			
		case APP_CMD_DESTROY:
			_userActivity->onDestroy();
			break;
			
		case APP_CMD_SAVE_STATE:
			_userActivity->onSaveInstanceState(&state->savedState);
			break;
			
		//case APP_CMD_WINDOW_REDRAW_NEEDED:
		//	break;
	}
}

int Engine::inputProc(AInputEvent* event)
{
	int type = AInputEvent_getType(event);
	if (type == AINPUT_EVENT_TYPE_MOTION)
	{
		MotionEvent motion(event);
		_userActivity->onTouchEvent(motion);
		return 1;
	}
	return 0;
}

void Engine::activityCall(android_app* state, int cmd)
{
	Engine* me = (Engine*) state->userData;
	if (me != nullptr)
	{
		me->activityProc(cmd);
	}
}

int Engine::inputCall(android_app* state, AInputEvent* event)
{
	Engine* me = (Engine*) state->userData;
	if (me != nullptr)
	{
		return me->inputProc(event);
	}
	return 0;
}
} // anut namespace
