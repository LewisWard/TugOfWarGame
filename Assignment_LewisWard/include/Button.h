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
	
	Button(math::vec2 origin, math::vec2 end) : m_o(origin), m_e(end) {};

	bool clicked(math::vec2 mouse);

	inline math::vec2 origin()
	{ return m_o; }

	inline math::vec2 end()
	{ return m_e; }

private:
	math::vec2 m_o; ///< origin
	math::vec2 m_e; ///< end
};

}; /// end of namespace gui
