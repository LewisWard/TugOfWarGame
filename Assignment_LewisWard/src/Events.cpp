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
void EventHandler::update()
{
	// process SDL events
	while(SDL_PollEvent(&m_event))
	{
		switch(m_event.type)
		{
		case SDL_WINDOWEVENT: std::cout<<"SDL_WINDOWEVENT\n";
			break;
		case SDL_KEYDOWN: std::cout<<"SDL_KEYDOWN\n";
			break;
		case SDL_KEYUP: std::cout<<"SDL_KEYUP\n";
			break;
		case SDL_MOUSEMOTION: std::cout<<"SDL_MOUSEMOTION\n";
			break;
		case SDL_MOUSEBUTTONDOWN: std::cout<<"SDL_MOUSEBUTTONDOWN\n";
			break;
		case SDL_MOUSEBUTTONUP: std::cout<<"SDL_MOUSEBUTTONUP\n";
			break;
		case SDL_MOUSEWHEEL: std::cout<<"SDL_MOUSEWHEEL\n";
			break;
		case SDL_QUIT: m_playState = false; ///< quit window/program
			break;
		}
	}
}
