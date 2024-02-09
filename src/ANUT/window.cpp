#include "ANUT/window.h"
#include "android_native_app_glue.h"
#include <EGL/eglext.h>
#include <cstring>
#include <vector>

#define EGL_CALL(fcall)                   \
        fcall;                            \
        if (eglGetError() != EGL_SUCCESS) \
            return false;

Window::Window()
{
	memset(this, 0, sizeof(Window));
}

bool Window::Init(ANativeWindow* window)
{
	const int window_attributes[] =
	{
		//EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		//EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_NONE
	};
	
	const int render_buffer[] =
	{
		EGL_RENDER_BUFFER, EGL_BACK_BUFFER,
		EGL_NONE
	};
	
	const int gles_version[] =
	{
		EGL_CONTEXT_MAJOR_VERSION_KHR, 3,
		EGL_CONTEXT_MINOR_VERSION_KHR, 2,
		EGL_NONE
	};
	
	display = EGL_CALL(eglGetDisplay(EGL_DEFAULT_DISPLAY));
	EGL_CALL(eglInitialize(display, nullptr, nullptr));
	
	if (!ChooseConfig(window_attributes))
	{
		return false;
	}
	
	surface = EGL_CALL(eglCreateWindowSurface(display, config, window, render_buffer));
	context = EGL_CALL(eglCreateContext(display, config, EGL_NO_CONTEXT, gles_version));
	EGL_CALL(eglMakeCurrent(display, surface, surface, context));
	EGL_CALL(eglSwapInterval(display, 0));
	
	width = ANativeWindow_getWidth(window);
	height = ANativeWindow_getHeight(window);
	open = true;
	
	return true;
}

bool Window::ChooseConfig(const int attributes[])
{
	int configs_count;
	EGL_CALL(eglChooseConfig(display, attributes, nullptr, 0, &configs_count));
	std::vector<EGLConfig> matches;
	matches.resize(configs_count);
	EGL_CALL(eglChooseConfig(display, attributes, matches.data(), configs_count, &configs_count));
	
	for (int i = 0; i < configs_count; i++)
	{
		if (MatchConfig(matches[i], attributes))
		{
			config = matches[i];
			return true;
		}
	}
	return false;
}

bool Window::MatchConfig(EGLConfig target, const int attributes[])
{
	for (int i = 0; attributes[i] != EGL_NONE; i+=2)
	{
		int value;
		EGL_CALL(eglGetConfigAttrib(display, target, attributes[i], &value));
		if (value != attributes[i+1])
		{
			return false;
		}
	}
	return true;
}

void Window::Destroy()
{
	// nullptr = EGL_NO_*
	
	if (display == nullptr)
	{
		return;
	}
	
	eglMakeCurrent(display, nullptr, nullptr, nullptr);
	if (context != nullptr)
	{
		eglDestroyContext(display, context);
	}
	if (surface != nullptr)
	{
		eglDestroySurface(display, surface);
	}
	
	eglTerminate(display);
	
	memset(this, 0, sizeof(Window));
}
