// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#pragma once
#include "Button.h"
#include "Window.h"
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

	Menu(uint32_t texture) : m_texture(texture) {};
	~Menu();

	void bind() const;

	void unbind() const;

	inline void addButton(Button b)
	{ m_buttons.push_back(b); }

	inline void deleteButton()
	{ m_buttons.pop_back(); }

private:
	uint32_t m_texture; ///< texture of menu
	std::vector<Button> m_buttons; ///< buttons on menu
};

//----------------------------------------------------------------------------------------------------------------------
/// \brief  A group of menus
//----------------------------------------------------------------------------------------------------------------------
class Menus
{
public:

	Menus(Menu menu);
	~Menus();

	void draw() const;

	inline void addMenu(Menu m)
	{ m_menus.push_back(m); }

	inline void deleteMenu()
	{ m_menus.pop_back(); }

	inline void activeMenu(int active)
	{ m_active = active; }

private:
	uint32_t m_vbo; ///< VBO
	uint32_t m_ibo; ///< IBO
	std::vector<Menu> m_menus; ///< menus
	int m_active; ///< what is the active menu (one we are one/want)
};

}; /// end of namespace gui
