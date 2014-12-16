// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#include "Events.h"

EventHandler::EventHandler()
{
	m_playState = true;
}
EventHandler::~EventHandler()
{

}
int EventHandler::update()
{
	// process SDL events
	while(SDL_PollEvent(&m_event))
	{
		switch(m_event.type)
		{
		case SDL_WINDOWEVENT:
			break;
		case SDL_KEYDOWN:
				if(SDLK_0 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 0\n"; return k0;}
				if(SDLK_1 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 1\n"; return k1;}
				if(SDLK_2 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 2\n"; return k2;}
				if(SDLK_3 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 3\n"; return k3;}
				if(SDLK_4 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 4\n"; return k4;}
				if(SDLK_5 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 5\n"; return k5;}
				if(SDLK_6 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 6\n"; return k6;}
				if(SDLK_7 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 7\n"; return k7;}
				if(SDLK_8 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 8\n"; return k8;}
				if(SDLK_9 == m_event.key.keysym.sym)
				{std::cout<<"Pressed: 9\n"; return k9;}
				if(SDLK_q == m_event.key.keysym.sym)
				{std::cout<<"Pressed: Q\n"; return kQ;}
				if(SDLK_w == m_event.key.keysym.sym)
				{std::cout<<"Pressed: W\n"; return kW;}
				if(SDLK_e == m_event.key.keysym.sym)
				{std::cout<<"Pressed: E\n"; return kE;}
				if(SDLK_a == m_event.key.keysym.sym)
				{std::cout<<"Pressed: A\n"; return kA;}
				if(SDLK_s == m_event.key.keysym.sym)
				{std::cout<<"Pressed: S\n"; return kS;}
				if(SDLK_d == m_event.key.keysym.sym)
				{std::cout<<"Pressed: D\n"; return kD;}
				if(SDLK_SPACE == m_event.key.keysym.sym)
				{std::cout<<"Pressed: Space\n"; return kSpace;}

				// key that I'm not worried about has been pressed
				return kNONE;
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEMOTION:
			// update mouse position
			m_mouse.x = m_event.motion.x;
			m_mouse.y = m_event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (SDL_BUTTON_LEFT == m_event.button.button)
			{
				std::cout << "Mouse Pressed: Left\n";
				return kMDL;
			}
			if (SDL_BUTTON_MIDDLE == m_event.button.button)
			{
				std::cout << "Mouse Pressed: Middle\n";
				return kMDM;
			}
			if (SDL_BUTTON_RIGHT == m_event.button.button)
			{
				std::cout << "Mouse Pressed: Right\n";
				return kMDR;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			// mouse buttons released
			if (SDL_BUTTON_LEFT)
			{
				std::cout << "Mouse Released: Left\n";
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUL;
			}
			if (SDL_BUTTON_MIDDLE)
			{
				std::cout << "Mouse Released: Middle\n";
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUM;
			}
			if (SDL_BUTTON_RIGHT)
			{
				std::cout << "Mouse Released: Right\n";
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUR;
			}
			break;
		case SDL_MOUSEWHEEL:
			break;
		case SDL_QUIT: m_playState = false; ///< quit window/program
			break;
		}
	}
}
