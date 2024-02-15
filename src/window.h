#if not defined(ANUT_WINDOW_H)
#define ANUT_WINDOW_H
#include <EGL/egl.h>

class Window
{
public:
	static int red_size, green_size, blue_size, alpha_size,
	           min_depth_size, min_stencil_size;
	
	Window();
	
	bool Init(ANativeWindow* window);
	void Destroy();
	
	int Width() const;
	int Height() const;
	float AspectRatio() const;
	bool IsOpen() const;
	void Display() const;
	
private:
	bool ChooseConfig(const int attributes[]);
	bool MatchConfig(EGLConfig target, const int attributes[]);
	bool IsMinAttrValue(int attribute);
	
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

inline void Window::Display() const
{
	eglSwapBuffers(display, surface);
}

#endif
