#include <android/native_activity.h>
#include <android/window.h>
#include "android_native_app_glue.h"
#include "activity.h"
#include "engine.h"
#include "input.h"
#include "utils/timer.h"
#include "window.h"

Window* Engine::window = nullptr;
Input*  Engine::input = nullptr;

Engine::Engine(android_app* app)
{
	window = new Window;
	input = new Input;
	counter = new Timer;
	
	android = app;
	android->userData = (void*) this;
	android->onInputEvent = Input::InputProc;
	android->onAppCmd = 
	[](android_app* app, int cmd)
	{
		Engine* anut = (Engine*) app->userData;
		if (anut)
			anut->ActivityProc(cmd);
	};
	
	exit_code = 0;
	main_activity = nullptr;
	
	Activity::window = window;
	Activity::input = input;
	Activity::engine = this;
}

Engine::~Engine()
{
	delete window;
	delete input;
	delete counter;
}

int Engine::Start(Activity* main_act)
{
	main_activity = main_act;
	main_activity->OnCreate(android->savedState);
	state = STOPPED;
	
	while (true)
	{
		android_poll_source* source;
		int ident, fd, event;
		while ((ident=ALooper_pollOnce(state, &fd, &event, (void**) &source)) >= 0)
		{
			if (source)
			{
				source->process(android, source);
			}
			if (android->destroyRequested != 0)
			{
				return exit_code;
			}
		}
		main_activity->OnDrawFrame();
		window->Display();
		main_activity->OnUpdate(counter->Restart());
	}
}

void Engine::Abort(int status, std::string msg)
{
	ANativeActivity_finish(android->activity);
	exit_code = status;
	message = msg;
	state = STOPPED;
}

void Engine::ActivityProc(int cmd)
{
	switch (cmd)
	{
		case APP_CMD_START:
			main_activity->OnStart();
			return;
			
		case APP_CMD_RESUME:
			main_activity->OnResume();
			break;
			
		case APP_CMD_INIT_WINDOW:
			if (!window->Init(android->window))
			{
				Abort(-1);
				break;
			}
			ANativeActivity_setWindowFlags(android->activity, AWINDOW_FLAG_FULLSCREEN, 0);
			main_activity->OnSurfaceChanged(window->Width(), window->Height());
			main_activity->OnSurfaceCreated();
			counter->Start();
			state = RUNNING;
			break;
			
		case APP_CMD_GAINED_FOCUS:
			main_activity->OnGainedFocus();
			break;
			
		case APP_CMD_PAUSE:
			main_activity->OnPause();
			break;
			
		case APP_CMD_LOST_FOCUS:
			main_activity->OnLostFocus();
			break;
			
		case APP_CMD_STOP:
			main_activity->OnStop();
			break;
			
		case APP_CMD_TERM_WINDOW:
			counter->Pause();
			state = STOPPED;
			window->Destroy();
			break;
			
		case APP_CMD_DESTROY:
			main_activity->OnDestroy();
			break;
			
		case APP_CMD_SAVE_STATE:
			main_activity->OnSaveInstanceState(&android->savedState);
			break;
			
		case APP_CMD_WINDOW_REDRAW_NEEDED:
			//main_activity->Redraw();
			break;
	}
}

