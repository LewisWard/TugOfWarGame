// author : Lewis Ward (http://www.lewis-ward.com)
// program: Tug Of War Game
// date   : 17/11/2014
// � 2016 Lewis Ward. All rights reserved.
#pragma once
#define GLEW_STATIC
#include "gl/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	//----------------------------------------------------------------------------------------------------------------------
	Window();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Window();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the title of the window
	/// \parma const char* new name for thw window
	//----------------------------------------------------------------------------------------------------------------------
	void setTitle(const char* title);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the icon of the window
	/// \parma SDL_Surface* add a icon to the window
	//----------------------------------------------------------------------------------------------------------------------
	void setIcon(SDL_Surface* icon);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the window pointer
	/// \return SDL_Window*
	//----------------------------------------------------------------------------------------------------------------------
	inline SDL_Window* getWindow() { return m_windowSDL; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the window width
	/// \return int
	//----------------------------------------------------------------------------------------------------------------------
	inline int width() { return m_winW; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the window height
	/// \return int
	//----------------------------------------------------------------------------------------------------------------------
	inline int height() { return m_winH; }

private:
	int m_winX; ///< x position
	int m_winY; ///< y position
	int m_winW; ///< window width
	int m_winH; ///< window height
	SDL_Window* m_windowSDL; ///< SDL window
	SDL_GLContext m_windowGL; ///< OpenGL window handle
};
