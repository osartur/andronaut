#if not defined(ANUT_INPUT_H)
#define ANUT_INPUT_H

class android_app;
class AInputEvent;

class Input
{
public:
	static int InputProc(android_app* app, AInputEvent* event);
	
	Input();
	virtual ~Input();
	
	bool FingerDown(int finger_id);
	bool FingerPressed(int finger_id);
	
	float FingerX(int finger_id);
	float FingerY(int finger_id);
	
private:
	static void HandleMotion(AInputEvent* event);
	
	struct Finger
	{
		float x;
		float y;
		bool control;
		bool down;
	}
	static fingers[10];
};


inline bool Input::FingerDown(int finger_id)
{
	return fingers[finger_id].down;
}

inline bool Input::FingerPressed(int finger_id)
{
	if (fingers[finger_id].control)
	{
		fingers[finger_id].control = false;
		return true;
	}
	return false;
}

inline float Input::FingerX(int finger_id)
{
	return fingers[finger_id].x;
}

inline float Input::FingerY(int finger_id)
{
	return fingers[finger_id].y;
}

#endif
