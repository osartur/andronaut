#if not defined(ANUT_WINDOW_H)
#define ANUT_WINDOW_H
#include <EGL/egl.h>
#include <android/native_activity.h>
#include <android/window.h>

class Window
{
public:
	static int redSize, greenSize, blueSize, alphaSize,
	           minDepthSize, minStencilSize;
	
	Window();
	
	bool init(ANativeWindow* hNW, ANativeActivity* hNA);
	void destroy();
	
	int width() const;
	int height() const;
	float aspectRatio() const;
	
	void display() const;
	void setFlags(unsigned flags, unsigned mask);
	
private:
	bool chooseConfig(const int attributes[]);
	bool matchConfig(EGLConfig target, const int attributes[]);
	bool isRestrictedAttrib(int attribute);
	
	EGLDisplay _display;
	EGLConfig  _config;
	EGLSurface _surface;
	EGLContext _context;
	ANativeActivity* _activity;
	int _width;
	int _height;
	float _aspect;
};


inline int Window::width() const
{
	return _width;
}

inline int Window::height() const
{
	return _height;
}

inline float Window::aspectRatio() const
{
	return _aspect;
}

inline void Window::display() const
{
	eglSwapBuffers(_display, _surface);
}

inline void Window::setFlags(unsigned flags, unsigned mask)
{
	ANativeActivity_setWindowFlags(_activity, flags, mask);
}

#endif
