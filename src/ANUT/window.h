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
	bool ChooseConfig(const int attributes[]);
	bool MatchConfig(EGLConfig config, const int attributes[]);
	
	EGLDisplay m_display;
	EGLConfig  m_config;
	EGLSurface m_surface;
	EGLContext m_context;
	int m_width;
	int m_height;
	bool m_open;
};


inline int Window::Width() const
{
	return m_width;
}

inline int Window::Height() const
{
	return m_height;
}

inline bool Window::IsOpen() const
{
	return m_open;
}

inline void Window::Display()
{
	eglSwapBuffers(m_display, m_surface);
}

#endif
