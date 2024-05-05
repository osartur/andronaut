#include <android/native_activity.h>
#include <android/window.h>
#include <android/input.h>
#include "android_native_app_glue.h"
#include "activity.h"
#include "engine.h"
#include "window.h"

Window* Engine::window = nullptr;

Engine::Engine(android_app* app)
{
	window = new Window;
	
	_android = app;
	_android->userData = this;
	_android->onAppCmd = activityCall;
	_android->onInputEvent = inputCall;
	
	_exitCode = 0;
	
	Activity::window = window;
	Activity::engine = this;
}

Engine::~Engine()
{
	delete window;
}

int Engine::run(Activity* activity)
{
	_activity = activity;
	_activity->onCreate(_android->savedState);
	_state = STOPPED;
	
	while (true)
	{
		android_poll_source* source = nullptr;
		int fd, event;
		while (ALooper_pollOnce(_state, &fd, &event, (void**) &source) >= 0)
		{
			if (source != nullptr)
			{
				source->process(_android, source);
			}
			if (_android->destroyRequested != 0)
			{
				return _exitCode;
			}
		}
		_activity->onDrawFrame();
		window->display();
	}
}

void Engine::finish(int status)
{
	ANativeActivity_finish(_android->activity);
	_state = STOPPED;
	_exitCode = status;
}

void Engine::activityProc(int cmd)
{
	switch (cmd)
	{
		case APP_CMD_START:
			_activity->onStart();
			break;
			
		case APP_CMD_RESUME:
			_activity->onResume();
			break;
			
		case APP_CMD_INIT_WINDOW:
			if (!window->init(_android->window, _android->activity))
			{
				finish(-1);
				break;
			}
			_activity->onSurfaceCreated();
			_activity->onSurfaceChanged(window->width(), window->height());
			_state = RUNNING;
			break;
			
		case APP_CMD_GAINED_FOCUS:
			_activity->onGainedFocus();
			break;
			
		case APP_CMD_PAUSE:
			_activity->onPause();
			break;
			
		case APP_CMD_LOST_FOCUS:
			_activity->onLostFocus();
			break;
			
		case APP_CMD_STOP:
			_activity->onStop();
			break;
			
		case APP_CMD_TERM_WINDOW:
			window->destroy();
			_activity->onSurfaceDestroyed();
			_state = STOPPED;
			break;
			
		case APP_CMD_DESTROY:
			_activity->onDestroy();
			break;
			
		case APP_CMD_SAVE_STATE:
			_activity->onSaveInstanceState(&_android->savedState);
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
		_activity->onTouchEvent(motion);
		return 1;
	}
	return 0;
}

void Engine::activityCall(android_app* _android, int cmd)
{
	Engine* me = (Engine*) _android->userData;
	if (me != nullptr)
	{
		me->activityProc(cmd);
	}
}

int Engine::inputCall(android_app* _android, AInputEvent* event)
{
	Engine* me = (Engine*) _android->userData;
	if (me != nullptr)
	{
		return me->inputProc(event);
	}
	return 0;
}
