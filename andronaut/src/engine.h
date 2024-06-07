#if not defined(ANUT_ENGINE_H)
#define ANUT_ENGINE_H
#include <string>

class android_app;
class AInputEvent;

namespace anut
{
class Window;
class Activity;

class Engine
{
public:
	static Window* window;
	static android_app* state;
	
	static void finish(int status);
	
	Engine(android_app* app);
	virtual ~Engine();
	
	int run(Activity* activity);
	
private:
	static int inputProc(android_app* android, AInputEvent* event);
	static void activityProc(android_app* android, int cmd);
	
	enum State : int
	{
		STOPPED = -1,
		RUNNING = 0
	};
	
	static int loopState;
	static int exitCode;
	static Activity* userActivity;
};
} // anut namespace

#endif
