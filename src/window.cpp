#include "window.h"
#include "android_native_app_glue.h"
#include <EGL/eglext.h>
#include <cstring>
#include <vector>

int Window::redSize = 8;
int Window::blueSize = 8;
int Window::greenSize = 8;
int Window::alphaSize = 8;
int Window::minDepthSize = 0;
int Window::minStencilSize = 0;

#define EGL_CALL(fcall)                   \
        fcall;                            \
        if (eglGetError() != EGL_SUCCESS) \
            return false;

Window::Window()
{
	memset(this, 0, sizeof(Window));
}

bool Window::init(ANativeWindow* hNW, ANativeActivity* hNA)
{
	const int windowAttributes[] =
	{
		//EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		//EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
		EGL_RED_SIZE, redSize,
		EGL_GREEN_SIZE, greenSize,
		EGL_BLUE_SIZE, blueSize,
		EGL_ALPHA_SIZE, alphaSize,
		EGL_DEPTH_SIZE, minDepthSize,
		EGL_STENCIL_SIZE, minStencilSize,
		EGL_NONE
	};
	
	const int renderBuffer[] =
	{
		EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
		EGL_NONE
	};
	
	const int glesVersion[] =
	{
		EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
		EGL_CONTEXT_MINOR_VERSION_KHR, 2,
		EGL_NONE
	};
	
	_display = EGL_CALL(eglGetDisplay(EGL_DEFAULT_DISPLAY));
	EGL_CALL(eglInitialize(_display, nullptr, nullptr));
	
	if (!chooseConfig(windowAttributes))
	{
		return false;
	}
	
	_surface = EGL_CALL(eglCreateWindowSurface(_display, _config, hNW, renderBuffer));
	_context = EGL_CALL(eglCreateContext(_display, _config, EGL_NO_CONTEXT, glesVersion));
	EGL_CALL(eglMakeCurrent(_display, _surface, _surface, _context));
	EGL_CALL(eglSwapInterval(_display, 0));
	
	_activity = hNA;
	_width = ANativeWindow_getWidth(hNW);
	_height = ANativeWindow_getHeight(hNW);
	_aspect = (float) _width / (float) _height;
	
	return true;
}

bool Window::chooseConfig(const int attributes[])
{
	int configsCount;
	EGL_CALL(eglChooseConfig(_display, attributes, nullptr, 0, &configsCount));
	std::vector<EGLConfig> matches;
	matches.resize(configsCount);
	EGL_CALL(eglChooseConfig(_display, attributes, matches.data(), configsCount, &configsCount));
	
	for (int i = 0; i < configsCount; i++)
	{
		if (matchConfig(matches[i], attributes))
		{
			_config = matches[i];
			return true;
		}
	}
	return false;
}

bool Window::matchConfig(EGLConfig target, const int attributes[])
{
	for (int i = 0; attributes[i] != EGL_NONE; i+=2)
	{
		int value;
		EGL_CALL(eglGetConfigAttrib(_display, target, attributes[i], &value));
		int required = attributes[i+1];
		
		if (isRestrictedAttrib(attributes[i]))
		{
			if (value != required)
			{
				return false;
			}
		}
		else if (value < required)
		{
			return false;
		}
	}
	return true;
}

bool Window::isRestrictedAttrib(int attribute)
{
	return attribute != EGL_DEPTH_SIZE
	    && attribute != EGL_STENCIL_SIZE
	    && attribute != EGL_SAMPLE_BUFFERS
	    && attribute != EGL_SAMPLES;
}

void Window::destroy()
{
	// nullptr = EGL_NO_*
	
	if (_display == nullptr)
	{
		return;
	}
	
	eglMakeCurrent(_display, nullptr, nullptr, nullptr);
	if (_context != nullptr)
	{
		eglDestroyContext(_display, _context);
	}
	if (_surface != nullptr)
	{
		eglDestroySurface(_display, _surface);
	}
	
	eglTerminate(_display);
	
	memset(this, 0, sizeof(Window));
}
