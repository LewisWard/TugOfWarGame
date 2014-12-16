// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
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
	
	Button(math::vec3 origin, math::vec3 end) : m_o(origin), m_e(end) {};

	inline math::vec3 origin()
	{ return m_o; }

	inline math::vec3 end()
	{ return m_e; }

private:
	math::vec3 m_o; ///< origin
	math::vec3 m_e; ///< end
};

}; /// end of namespace gui
