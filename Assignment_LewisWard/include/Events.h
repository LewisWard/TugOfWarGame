// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#pragma once
#include "Window.h"

// all the events that I require
enum events
{
	kNONE, k0, k1, k2, k3, k4, k5, k6, k7, k8, k9, ///< nothing pressed and 0->9 keys
	kQ, kW, kE, kA, kS, kD, ///< Q/W/E/A/S/D
	kSpace, ///< Space bar 
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Handles all input events
//----------------------------------------------------------------------------------------------------------------------
class EventHandler
{
public:
	///\brief Constructor
	EventHandler();
	///\brief Destructor
	~EventHandler();

	///\brief update events
	///\return int the event code (see events enum)
	int update();

	///\brief get the play state
	///\prama bool false to quit program
	inline bool playState()
	{ return m_playState; }

private:
	SDL_Event m_event;
	bool m_playState;
};
