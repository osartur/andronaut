#if not defined(ANUT_ENGINE_H)
#define ANUT_ENGINE_H
#include <string>

class android_app;
class AInputEvent;
class Window;
class Input;
class Activity;
class Timer;

struct ProgramExit
{
	int code;
	std::string message;
};

class Engine
{
public:
	static Window* window;
	
	Engine(android_app* app);
	virtual ~Engine();
	
	ProgramExit start(Activity* activity);
	void finish(int status, std::string msg = std::string());
	
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
	Input* _input;
	Timer* _counter;
	int _state;
	ProgramExit _output;
};

#endif
