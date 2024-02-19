#if not defined(ANUT_ENGINE_H)
#define ANUT_ENGINE_H
#include <string>

class android_app;
class AInputEvent;
class Window;
class Input;
class Activity;
class Timer;

class Engine
{
public:
	static Window* window;
	
	Engine(android_app* app);
	virtual ~Engine();
	
	int Start(Activity* main_act);
	void Abort(int status, std::string msg = std::string());
	std::string AbortMessage() const;
	
private:
	void ActivityProc(int cmd);
	int InputProc(AInputEvent* event);
	
	enum
	{
		STOPPED = -1,
		RUNNING = 0
	}
	state;
	
	android_app* android;
	Activity* main_activity;
	Input* input;
	Timer* counter;
	int exit_code;
	std::string message;
};


inline std::string Engine::AbortMessage() const
{
	return message;
}

#endif
