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
	bool IsOpen() const;
	void Display();
	
private:
	EGLDisplay display;
	EGLConfig  config;
	EGLSurface surface;
	EGLContext context;
	int width;
	int height;
	bool is_open;
};


inline int Window::Width() const
{
	return width;
}

inline int Window::Height() const
{
	return height;
}

inline bool Window::IsOpen() const
{
	return is_open;
}

inline void Window::Display()
{
	eglSwapBuffers(display, surface);
}

#endif
