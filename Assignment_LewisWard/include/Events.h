// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#pragma once
#include "Window.h"

class EventHandler
{
public:
	///\brief Constructor
	EventHandler();
	///\brief Destructor
	~EventHandler();

	///\brief update events
	void update();

	///\brief get the play state
	///\prama bool false to quit program
	inline bool playState()
	{ return m_playState; }

private:
	SDL_Event m_event;
	bool m_playState;
};
