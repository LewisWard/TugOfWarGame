// author : Lewis Ward
// program: Tog Of War Game
// date   : 17/11/2014
// © 2016 Lewis Ward. All rights reserved.
#include "Window.h"

bool initSDL()
{
	// initialisation of SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		// initialisation failed
		std::cout<<"Failed to initialise SDL"<<std::endl;
		return false;
	}
	// initialisation susscessful
	return true;
}
bool initGlew()
{
	// turn on glew experimental mode
	glewExperimental = GL_TRUE;
	// initialisation of glew
	GLenum error = glewInit();
	if(GLEW_OK != error)
	{
		// if there was an error
		std::cout<<"Error: GLEW failed\n";
		return false;
	}
	return true;
}


// Delta Time based upon link below: 
// http://phstudios.com/forums/index.php?/topic/175-c-directx-tutorial-tutorial-5-high-performance-timing-and-device-handling/
// http://msdn.microsoft.com/en-gb/library/windows/desktop/ms644905(v=vs.85).aspx
// gobal variables for dt
uint64_t g_startCount = 0, g_lastCount = 0, g_newTime = 0;
float g_CPS;

void initTimerDT()
{
	// get the current performance-counter frequency
	QueryPerformanceFrequency((LARGE_INTEGER*)&g_startCount);
	// compute Count Per Seconds (CPS)
	g_CPS = 1.0f / g_startCount;

	// setup previous time
	QueryPerformanceCounter((LARGE_INTEGER*)&g_lastCount);
}

float updateTimerDT()
{
	// get the current frequency
	QueryPerformanceCounter((LARGE_INTEGER*)&g_newTime);
	// compute the DT
	float dt = (g_newTime - g_lastCount) * g_CPS;
	// update last time value with new
	g_lastCount = g_newTime;
	// return dt
	return dt;
}

Window::Window()
{
	// set window position, width and height
	m_winX = 150;
	m_winY = 150;
	m_winW = 512;
	m_winH = 512;

	// create a SDL window
	m_windowSDL = SDL_CreateWindow("Window", m_winX, m_winY, m_winW, m_winH, 
								SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	// make a OpenGL Context from the window, based upon example found here:
	// https://wiki.libsdl.org/SDL_GL_CreateContext [accessed 17/11/14]
	// http://lazyfoo.net/tutorials/SDL/50_SDL_and_opengl_2/index.php [accessed 17/11/14]
	m_windowGL = SDL_GL_CreateContext(m_windowSDL);
	// make the openGL window current
	SDL_GL_MakeCurrent(m_windowSDL, m_windowGL);
	// creating the viewport
	glViewport(0, 0, m_winW, m_winH);
	// setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// multiply matrix with orthographic matrix
	glOrtho(0, m_winW, m_winH, 0, 0, 50);
	// modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// clear screen to set colour
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
}
Window::~Window()
{
	// delete windows
	SDL_DestroyWindow(m_windowSDL);
	SDL_GL_DeleteContext(m_windowGL);
}
void Window::setTitle(const char* title)
{
	SDL_SetWindowTitle(m_windowSDL, title);
}
void Window::setIcon(SDL_Surface* icon)
{
	SDL_SetWindowIcon(m_windowSDL, icon);
}
