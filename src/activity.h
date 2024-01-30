#if not defined(ANUT_ACTIVITY_H)
#define ANUT_ACTIVITY_H
#include "engine.h"

class android_app;
class Window;
class Input;

class Activity
{
public:
	static Window* window;
	static Input* input;
	static Engine* engine;
	
	virtual void OnCreate();
	virtual void OnStart();
	virtual void OnResume();
	virtual void OnPause();
	virtual void OnStop();
	virtual void OnDestroy();
	
	virtual void OnSurfaceCreated();
	virtual void OnSurfaceChanged(int w, int h);
	virtual void OnUpdate(float dt);
	virtual void OnDrawFrame();
	
	virtual void OnGainedFocus();
	virtual void OnLostFocus();
};

#endif
