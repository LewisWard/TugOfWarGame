// author : Lewis Ward
// program: Tug Of War Game
// date   : 14/12/2014
// © 2016 Lewis Ward. All rights reserved.
// For more details go to: http://www.lewis-ward.com/tog-of-war.html

#include "Menu.h"

namespace gui
{

Menu::Menu(uint32_t texture)
{
	m_texture = texture;
	// vertex array
	vertUV verts[4];
	// set vertex data
	verts[0].vertex.x = -1.0f;
	verts[0].vertex.y = 1.0f;
	verts[0].vertex.z = 0.0f;
	verts[0].uv.x = 0.0f;
	verts[0].uv.y = 0.0f;
	verts[1].vertex.x = 1.0f;
	verts[1].vertex.y = 1.0f;
	verts[1].vertex.z = 0.0f;
	verts[1].uv.x = 1.0f;
	verts[1].uv.y = 0.0f;
	verts[2].vertex.x = -1.0f;
	verts[2].vertex.y = -1.0f;
	verts[2].vertex.z = 0.0f;
	verts[2].uv.x = 0.0f;
	verts[2].uv.y = 1.0f;
	verts[3].vertex.x = 1.0f;
	verts[3].vertex.y = -1.0f;
	verts[3].vertex.z = 0.0f;
	verts[3].uv.x = 1.0f;
	verts[3].uv.y = 1.0f;
	// indices
	int indices[] =
	{
		0, 1, 2,
		2, 3, 1
	};

	// genereate a buffer
	glGenBuffers(1, &m_vbo);
	// bind
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &verts[0], GL_STATIC_DRAW);
	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// genereate a buffer
	glGenBuffers(1, &m_ibo);
	// bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)* 6, &indices[0], GL_STATIC_DRAW);
	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Menu::~Menu()
{
	// delete texture
	glDeleteTextures(1, &m_texture);

	// delete buffers
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}
int Menu::clickButton(math::vec2 mouse)
{
	bool test;
	// go over each button on the menu
	for (size_t i = 0; i < m_buttons.size(); ++i)
	{
		// test each button to see if its been clicked on
		test = m_buttons[i].clicked(mouse);
		if (test)
		{
			// return the button idex
			return i;
		}
	}
	return 100; ///< never going to have 100 buttons 
}
void Menu::draw()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// bind vbo and ibo buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	// an offset from NULL
	const float* offset = 0;
	// enable vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertUV), offset);
	glEnableVertexAttribArray(0);
	// enable (uv)
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertUV), offset + 4);
	glEnableVertexAttribArray(1);
	// draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// disable from modification
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}; /// end of namespace gui
