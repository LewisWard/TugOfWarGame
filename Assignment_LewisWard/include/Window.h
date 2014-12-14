// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#pragma once
#define GLEW_STATIC
#include "gl/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <Windows.h>
#include "Vec3.h"

//----------------------------------------------------------------------------------------------------------------------
/// \brief  SDL initialisation
/// \return bool true if SDL initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
bool initSDL();
//----------------------------------------------------------------------------------------------------------------------
/// \brief  GLEW initialisation
/// \return bool true if Glew initialisation was susscessful
//----------------------------------------------------------------------------------------------------------------------
bool initGlew();

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Delta Time 
//----------------------------------------------------------------------------------------------------------------------
void initTimerDT(); ///< initialisation
float updateTimerDT(); ///< update, return delta time

//----------------------------------------------------------------------------------------------------------------------
/// \brief  SDL/OpenGL Window
//----------------------------------------------------------------------------------------------------------------------
class Window 
{
public:
	///\brief Constructor
	Window();
	///\brief Destructor
	~Window();

	///\brief set the title of the window
	///\prama const char* new name for thw window
	void setTitle(const char* title);

	///\brief set the icon of the window
	///\prama SDL_Surface* add a icon to the window
	void setIcon(SDL_Surface* icon);

	///\brief get the window pointer
	///\return SDL_Window*
	inline SDL_Window* getWindow()
	{ return m_windowSDL; }

private:
	int m_winX; ///< x position
	int m_winY; ///< y position
	int m_winW; ///< window width
	int m_winH; ///< window height
	SDL_Window* m_windowSDL; ///< SDL window
	SDL_GLContext m_windowGL; ///< OpenGL window handle
};
