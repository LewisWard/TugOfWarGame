// author : Lewis Ward
// program: Tog Of War Game
// date   : 16/12/2014
// © 2016 Lewis Ward. All rights reserved.
#include "Button.h"

namespace gui
{

bool Button::clicked(math::vec2 mouse)
{
	// if mouse button was pressed on the button
	if (mouse.x >= m_o.x && mouse.y >= m_o.y && mouse.x <= m_e.x && mouse.y <= m_e.y)
	{
		// button clicked
		return true;
	}
	// button wasn't clicked
	return false;
}

}; /// end of namespace gui

