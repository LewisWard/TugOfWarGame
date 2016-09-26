// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 16/12/2014
#pragma once
#include "Button.h"
#include "Window.h"
#include "Events.h"
#include "Texture.h"
#include <vector>

namespace gui
{

//----------------------------------------------------------------------------------------------------------------------
/// \brief  A menu
//----------------------------------------------------------------------------------------------------------------------
class Menu
{
public:
	///\brief Constructor creates a menu
	///\prama uint32_t texutre
	Menu(uint32_t texture);
	///\brief Destructor
	~Menu();

	///\brief draw the menu
	void draw();

	///\brief detects if the button was clicked on
	///\prama math::vec2 mouse position
	///\return int button index (if not 100 a button was pressed)
	int clickButton(math::vec2 mouse);

	///\brief Adds a new button to the menu
	///\prama Button
	inline void addButton(Button b)
	{ m_buttons.push_back(b); }

	///\brief Removed last button added to the menu
	inline void deleteButton()
	{ m_buttons.pop_back(); }

private:
	std::vector<Button> m_buttons; ///< buttons on menu
	uint32_t m_vbo; ///< VBO
	uint32_t m_ibo; ///< IBO
	uint32_t m_texture; ///< texture
};

}; /// end of namespace gui
