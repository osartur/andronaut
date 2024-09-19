#include "vendor/android_native_app_glue.h"
#include "system/activity.h"
#include "system/engine.h"
#include "system/window.h"
#include <android/native_activity.h>
#include <android/window.h>
#include <android/input.h>

namespace anut
{
Window* Engine::window = nullptr;
android_app* Engine::state = nullptr;
int Engine::loopState = STOPPED;
int Engine::exitCode = 0;
Activity* Engine::userActivity = nullptr;

Engine::Engine(android_app* app)
{
	window = new Window;
	state = app;
	state->userData = nullptr;
	state->onAppCmd = activityProc;
	state->onInputEvent = inputProc;
}

Engine::~Engine()
{
	delete window;
}

int Engine::run(Activity* activity)
{
	userActivity = activity;
	userActivity->onCreate(state->savedState);
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
				if (state->destroyRequested != 0)
				{
					return exitCode;
				}
			}
		}
		userActivity->onProcessApp();
	}
}

void Engine::finish(int status)
{
	ANativeActivity_finish(state->activity);
	loopState = STOPPED;
	exitCode = status;
}

int Engine::inputProc(android_app* android, AInputEvent* event)
{
	return userActivity->onInputEvent(event);
}

void Engine::activityProc(android_app* android, int cmd)
{
	switch (cmd)
	{
		case APP_CMD_START:
			userActivity->onStart();
			break;
			
		case APP_CMD_RESUME:
			userActivity->onResume();
			break;
			
		case APP_CMD_INIT_WINDOW:
			if (!window->init(state->window, state->activity))
			{
				finish(-1);
				break;
			}
			userActivity->onSurfaceCreated();
			userActivity->onSurfaceChanged(window->getWidth(), window->getHeight());
			loopState = RUNNING;
			break;
			
		case APP_CMD_GAINED_FOCUS:
			userActivity->onGainedFocus();
			break;
			
		case APP_CMD_PAUSE:
			userActivity->onPause();
			break;
			
		case APP_CMD_LOST_FOCUS:
			userActivity->onLostFocus();
			break;
			
		case APP_CMD_STOP:
			userActivity->onStop();
			break;
			
		case APP_CMD_TERM_WINDOW:
			window->destroy();
			userActivity->onSurfaceDestroyed();
			loopState = STOPPED;
			break;
			
		case APP_CMD_DESTROY:
			userActivity->onDestroy();
			break;
			
		case APP_CMD_SAVE_STATE:
			userActivity->onSaveInstanceState(&state->savedState);
			break;
			
		//case APP_CMD_WINDOW_REDRAW_NEEDED:
		//	break;
	}
}

} // anut namespace
