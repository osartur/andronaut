#if not defined(ANUT_ACTIVITY_H)
#define ANUT_ACTIVITY_H
#include <android/input.h>

namespace anut
{
void* saveState(void* data, unsigned sizeInBytes);

class Activity
{
public:
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
	
	virtual void onProcessApp();
	virtual int onInputEvent(AInputEvent* event);
	
	virtual void onGainedFocus();
	virtual void onLostFocus();
};
} // anut namespace

#endif
