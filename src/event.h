#if not defined(ANUT_EVENT_H)
#define ANUT_EVENT_H

struct Event
{
	enum Type 
	{
		NONE = 0,
		FINGER_DOWN,
		FINGER_UP,
		FINGER_MOTION
	};
	
	struct Finger
	{
		int id;
		int x;
		int y;
	};
	
	int type = NONE;
	union
	{
		Finger touch;
	};
};

#endif
