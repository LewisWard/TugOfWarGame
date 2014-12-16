// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#include "Menu.h"

namespace gui
{

Menu::~Menu()
{

}
void Menu::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
void Menu::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Menus::Menus(Menu menu)
{
	// active menu is zero
	m_active = 0;

	// push back the menu
	m_menus.push_back(menu);

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)*4, &verts[0], GL_STATIC_DRAW);
	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// genereate a buffer
	glGenBuffers(1, &m_ibo);
	// bind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*6, &indices[0], GL_STATIC_DRAW);
	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Menus::~Menus()
{
	// menu destructors
	for (size_t i = 0; i < m_menus.size(); ++i)
	{
		m_menus[i].~Menu();
	}

	// delete buffers
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}

void Menus::draw() const
{
	// bind texture
	m_menus[m_active].bind();

	// bind vbo and ibo buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// an offset from NULL
	const float* offset = 0;
	// enable vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vertUV), offset);
	glEnableVertexAttribArray(0);
	// enable (uv)
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vertUV), offset + 3);
	glEnableVertexAttribArray(1);

	// draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// disable from modification
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// unbind buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind texture
	m_menus[m_active].unbind();
}

}; /// end of namespace gui
