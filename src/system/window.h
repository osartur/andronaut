#if not defined(ANUT_WINDOW_H)
#define ANUT_WINDOW_H
#include <EGL/egl.h>
#include <android/native_activity.h>
#include <android/window.h>

namespace anut
{
class Window
{
public:
	static int redSize, greenSize, blueSize, alphaSize,
	           minDepthSize, minStencilSize;
	
	Window();
	
	bool init(ANativeWindow* hNW, ANativeActivity* hNA);
	void destroy();
	// use only after init the window (onSurfaceCreated)
	void display() const;
	void setFlags(unsigned flags, unsigned mask);
	void enableVSync();
	void disableVSync();
	int getWidth() const;
	int getHeight() const;
	float getAspectRatio() const;
	
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


inline int Window::getWidth() const
{
	return _width;
}

inline int Window::getHeight() const
{
	return _height;
}

inline float Window::getAspectRatio() const
{
	return _aspect;
}

} // anut namespace

#endif
