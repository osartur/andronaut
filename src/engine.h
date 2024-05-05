#if not defined(ANUT_ENGINE_H)
#define ANUT_ENGINE_H
#include <string>

class android_app;
class AInputEvent;
class Window;
class Activity;

class Engine
{
public:
	static Window* window;
	
	Engine(android_app* app);
	virtual ~Engine();
	
	int run(Activity* activity);
	void finish(int status);
	
private:
	static void activityCall(android_app* android, int cmd);
	static int inputCall(android_app* android, AInputEvent* event);
	void activityProc(int cmd);
	int inputProc(AInputEvent* event);
	
	enum State : int
	{
		STOPPED = -1,
		RUNNING = 0
	};
	
	android_app* _android;
	Activity* _activity;
	int _state;
	int _exitCode;
};

#endif
