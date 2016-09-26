// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 16/12/2014
#pragma once
#include "Vec3.h"

namespace gui
{

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Menu button
//----------------------------------------------------------------------------------------------------------------------
class Button
{
public:
	///\brief Constructor
	///\prama math::vec2 start of the button
	///\prama math::vec2 end of the button
	Button(math::vec2 origin, math::vec2 end) : m_o(origin), m_e(end) {};

	///\brief detects if the button was clicked on
	///\prama math::vec2 smouse position
	///\return bool button was clicked on or not
	bool clicked(math::vec2 mouse);

private:
	math::vec2 m_o; ///< origin
	math::vec2 m_e; ///< end
};

}; /// end of namespace gui
