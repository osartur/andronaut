#if not defined(ANUT_ACTIVITY_H)
#define ANUT_ACTIVITY_H
#include "event.h"

class android_app;
class Window;
class Engine;

void* saveState(void* data, unsigned sizeInBytes);

class Activity
{
public:
	static Window* window;
	static Engine* engine;
	
	virtual void onCreate(void* savedState);
	virtual void onStart();
	virtual void onResume();
	virtual void onPause();
	virtual void onStop();
	virtual void onDestroy();
	virtual void onSaveInstanceState(void** savedState);
	
	virtual void onSurfaceCreated();
	virtual void onSurfaceChanged(int w, int h);
	virtual void onSurfaceDestroyed();
	virtual void onDrawFrame();
	
	virtual void onTouchEvent(const MotionEvent& event);
	
	virtual void onGainedFocus();
	virtual void onLostFocus();
};

#endif
