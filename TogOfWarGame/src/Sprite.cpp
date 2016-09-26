// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 11/01/2015
#include "Sprite.h"

Sprite::Sprite(const char* textureFile, float x_size, float y_size)
{
	// create new texture
	m_texture = new Texture(textureFile);
	loadTextureFromFile = true;

	// offset a little from zero otherwise when times by dt, will result in zero!
	m_transition = 0.1f;

	// not an animating sprite so only one image
	m_totalTransitions = 1;
	m_lastTransition = 0;

	m_deathComplete = false;

	// idle
	m_state = 0;

	// vertex array
	vertUV verts[4];
	// set vertex data
	verts[0].vertex.x = -x_size;
	verts[0].vertex.y = y_size;
	verts[0].vertex.z = 0.0f;
	verts[0].uv.x = 0.0f;
	verts[0].uv.y = 0.0f;
	verts[1].vertex.x = x_size;
	verts[1].vertex.y = y_size;
	verts[1].vertex.z = 0.0f;
	verts[1].uv.x = 1.0f;
	verts[1].uv.y = 0.0f;
	verts[2].vertex.x = -x_size;
	verts[2].vertex.y = -y_size;
	verts[2].vertex.z = 0.0f;
	verts[2].uv.x = 0.0f;
	verts[2].uv.y = 1.0f;
	verts[3].vertex.x = x_size;
	verts[3].vertex.y = -y_size;
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
Sprite::Sprite(const char* textureFile, float x_size, float y_size, float& h, float& w, std::vector<float> frameCount)
{
	// create new texture
	m_texture = new Texture(textureFile);
	loadTextureFromFile = true;

	// offset a little from zero otherwise when times by dt, will result in zero!
	m_transition = 0.1f;
	m_lastTransition = 0;
	// total number of sprites in strip
	m_totalTransitions = w;

	m_deathComplete = false;

	// stop division by zero
	if (m_totalTransitions && h)
	{
		// split up uv for each sprite in strip
		m_uvDividesW = 1.0f / m_totalTransitions;
		m_uvDividesH = 1.0f / h;
	}
	else
	{
		m_uvDividesW = 0.0f;
		m_uvDividesH = 0.0f;
	}

	m_stateTransitions = frameCount;

	// idle
	m_state = 0;

	// set vertex data
	m_verts[0].vertex.x = -x_size;
	m_verts[0].vertex.y = y_size;
	m_verts[0].vertex.z = 0.0f;
	m_verts[0].uv.x = 0.0f;
	m_verts[0].uv.y = 0.0f;
	m_verts[1].vertex.x = x_size;
	m_verts[1].vertex.y = y_size;
	m_verts[1].vertex.z = 0.0f;
	m_verts[1].uv.x = m_uvDividesW;
	m_verts[1].uv.y = 0.0f;
	m_verts[2].vertex.x = -x_size;
	m_verts[2].vertex.y = -y_size;
	m_verts[2].vertex.z = 0.0f;
	m_verts[2].uv.x = 0.0f;
	m_verts[2].uv.y = m_uvDividesH;
	m_verts[3].vertex.x = x_size;
	m_verts[3].vertex.y = -y_size;
	m_verts[3].vertex.z = 0.0f;
	m_verts[3].uv.x = m_uvDividesW;
	m_verts[3].uv.y = m_uvDividesH;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
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
Sprite::Sprite(Texture& texture, float x_size, float y_size, float& h, float& w, std::vector<float> frameCount)
{
	// create new texture
	m_texture = &texture;
	loadTextureFromFile = false;

	// offset a little from zero otherwise when times by dt, will result in zero!
	m_transition = 0.1f;
	m_lastTransition = 0;
	// total number of sprites in strip
	m_totalTransitions = w;

	m_deathComplete = false;

	// stop division by zero
	if (m_totalTransitions && h)
	{
		// split up uv for each sprite in strip
		m_uvDividesW = 1.0f / m_totalTransitions;
		m_uvDividesH = 1.0f / h;
	}
	else
	{
		m_uvDividesW = 0.0f;
		m_uvDividesH = 0.0f;
	}

	m_stateTransitions = frameCount;

	// idle
	m_state = 0;

	// set vertex data
	m_verts[0].vertex.x = -x_size;
	m_verts[0].vertex.y = y_size;
	m_verts[0].vertex.z = 0.0f;
	m_verts[0].uv.x = 0.0f;
	m_verts[0].uv.y = 0.0f;
	m_verts[1].vertex.x = x_size;
	m_verts[1].vertex.y = y_size;
	m_verts[1].vertex.z = 0.0f;
	m_verts[1].uv.x = m_uvDividesW;
	m_verts[1].uv.y = 0.0f;
	m_verts[2].vertex.x = -x_size;
	m_verts[2].vertex.y = -y_size;
	m_verts[2].vertex.z = 0.0f;
	m_verts[2].uv.x = 0.0f;
	m_verts[2].uv.y = m_uvDividesH;
	m_verts[3].vertex.x = x_size;
	m_verts[3].vertex.y = -y_size;
	m_verts[3].vertex.z = 0.0f;
	m_verts[3].uv.x = m_uvDividesW;
	m_verts[3].uv.y = m_uvDividesH;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
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
Sprite::~Sprite()
{
	// delete texture
	if (loadTextureFromFile)
	{ delete m_texture; }
	else
	{ m_texture = NULL; }

	m_stateTransitions.clear();

	m_stateTransitions.clear();

	// delete buffers
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}
void Sprite::draw()
{
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
}
void Sprite::update(float dt)
{
	// increase the transition
	m_transition += 10.0f * dt;

	switch (m_state)
	{
	case 0:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[3].uv.x += m_uvDividesW;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 1:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = m_uvDividesH + m_uvDividesH;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 2:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = m_uvDividesH + m_uvDividesH + m_uvDividesH;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = m_uvDividesH + m_uvDividesH + m_uvDividesH;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 3:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = 1.0f -  m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = 1.0f - m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = 1.0f;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = 1.0f;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
				m_deathComplete = true;
			}
		}
		break;
	}
}
void Sprite::update(float dt, math::Mat3 matrix)
{
	// increase the transition
	m_transition += 10.0f * dt;

	switch (m_state)
	{
	case 0:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = 0.0f;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = 0.0f;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = m_uvDividesH;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = m_uvDividesH;


			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 1:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = m_uvDividesH + m_uvDividesH;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 2:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1))
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = m_uvDividesH + m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = m_uvDividesH + m_uvDividesH + m_uvDividesH;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = m_uvDividesH + m_uvDividesH + m_uvDividesH;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
			}
		}
		break;
	case 3:
		// update uv co-ordinates 
		if (m_transition > (m_lastTransition + 1) && m_deathComplete == false)
		{
			m_verts[0].uv.x += m_uvDividesW;
			m_verts[0].uv.y = 1.0f - m_uvDividesH;
			m_verts[1].uv.x += m_uvDividesW;
			m_verts[1].uv.y = 1.0f - m_uvDividesH;
			m_verts[2].uv.x += m_uvDividesW;
			m_verts[2].uv.y = 1.0f;
			m_verts[3].uv.x += m_uvDividesW;
			m_verts[3].uv.y = 1.0f;

			// bind
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			// update the data
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
			// unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// increase the last transition
			m_lastTransition++;
			// reset animation once got to the end of cycle
			if (m_lastTransition >= m_stateTransitions[m_state])
			{
				m_verts[0].uv.x = 0.0f;
				m_verts[1].uv.x = m_uvDividesW;
				m_verts[2].uv.x = 0.0f;
				m_verts[3].uv.x = m_uvDividesW;

				// bind
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				// update the data
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertUV)* 4, &m_verts[0], GL_STATIC_DRAW);
				// unbind
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// increase the last transition
				m_lastTransition = 0;
				m_transition = 0.0f;
				m_deathComplete = true;
			}
		}
		break;
	}

	m_matrix = matrix;
}
void Sprite::bindSprite()
{
	m_texture->bind(0);
}

void Sprite::unbindSprite()
{
	m_texture->unbind();
}
