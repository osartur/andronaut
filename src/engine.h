#if not defined(ANUT_ENGINE_H)
#define ANUT_ENGINE_H

class android_app;
class Window;
class Input;
class Activity;
class Timer;

class Engine
{
public:
	static Window* window;
	static Input* input;
	
	Engine(android_app* app);
	virtual ~Engine();
	
	int Start(Activity* main_act);
	void Abort(int status);
	
private:
	void ActivityProc(int cmd);
	
	enum
	{
		STOPPED = -1,
		RUNNING = 0
	}
	state;
	
	android_app* android;
	Activity* main_activity;
	Timer* counter;
	int exit_code;
};

#endif
