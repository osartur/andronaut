#if not defined(ANUT_ACTIVITY_H)
#define ANUT_ACTIVITY_H
#include "event.h"

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
	virtual void onUpdate();
	
	virtual void onTouchEvent(const MotionEvent& event);
	
	virtual void onGainedFocus();
	virtual void onLostFocus();
};
} // anut namespace

#endif
