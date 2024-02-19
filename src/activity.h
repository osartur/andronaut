#if not defined(ANUT_ACTIVITY_H)
#define ANUT_ACTIVITY_H
#include "engine.h"
#include "event.h"

class android_app;
class Window;

class Activity
{
public:
	static Window* window;
	static Engine* engine;
	
	virtual void OnCreate(void* saved_state);
	virtual void OnStart();
	virtual void OnResume();
	virtual void OnPause();
	virtual void OnStop();
	virtual void OnDestroy();
	virtual void OnSaveInstanceState(void** saved_state);
	
	virtual void OnSurfaceCreated();
	virtual void OnSurfaceChanged(int w, int h);
	virtual void OnUpdate(const Event& event, float dt);
	virtual void OnDrawFrame();
	
	virtual void OnGainedFocus();
	virtual void OnLostFocus();
};

#endif
