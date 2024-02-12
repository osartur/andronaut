#if not defined(ANUT_WINDOW_H)
#define ANUT_WINDOW_H
#include <EGL/egl.h>

class Window
{
public:
	Window();
	
	bool Init(ANativeWindow* window);
	void Destroy();
	
	int Width() const;
	int Height() const;
	float AspectRatio() const;
	bool IsOpen() const;
	void Display();
	
private:
	bool ChooseConfig(const int attributes[]);
	bool MatchConfig(EGLConfig target, const int attributes[]);
	
	EGLDisplay display;
	EGLConfig  config;
	EGLSurface surface;
	EGLContext context;
	int width;
	int height;
	float aspect;
	bool open;
};


inline int Window::Width() const
{
	return width;
}

inline int Window::Height() const
{
	return height;
}

inline float Window::AspectRatio() const
{
	return aspect;
}

inline bool Window::IsOpen() const
{
	return open;
}

inline void Window::Display()
{
	eglSwapBuffers(display, surface);
}

#endif
