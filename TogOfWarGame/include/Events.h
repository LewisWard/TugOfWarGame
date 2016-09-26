// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#pragma once
#include "Window.h"

// all the events that I require
enum events
{
	kNONE, ///< nothing pressed
	kSpace, ///< Space bar 
	kMDL, kMDM, kMDR, ///< Mouse Down Left/Middle/Right
	kMUL, kMUM, kMUR, ///< Mouse Up Left/Middle/Right
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

	///\brief update mouse position
	///\return math::vec2 new mouse position
	inline math::vec2 mouseUpdate()
	{ return m_mouse; }

private:
	SDL_Event m_event;
	math::vec2 m_mouse;
	bool m_playState;
};