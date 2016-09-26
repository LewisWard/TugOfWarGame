// author : Lewis Ward
// program: Tog Of War Game
// date   : 17/11/2014
// © 2016 Lewis Ward. All rights reserved.
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
				if(SDLK_SPACE == m_event.key.keysym.sym)
				{return kSpace;}
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
			{ return kMDL; }
			if (SDL_BUTTON_MIDDLE == m_event.button.button)
			{ return kMDM; }
			if (SDL_BUTTON_RIGHT == m_event.button.button)
			{ return kMDR; }
			break;
		case SDL_MOUSEBUTTONUP:
			// mouse buttons released
			if (SDL_BUTTON_LEFT)
			{
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUL;
			}
			if (SDL_BUTTON_MIDDLE)
			{
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUM;
			}
			if (SDL_BUTTON_RIGHT)
			{
				m_mouse.x = m_event.motion.x;
				m_mouse.y = m_event.motion.y;
				return kMUR;
			}
			break;
		case SDL_QUIT: m_playState = false; ///< quit window/program
			break;
		}
	}
}
