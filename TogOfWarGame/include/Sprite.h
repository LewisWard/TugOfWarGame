// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 11/01/2015
#pragma once
#include "Texture.h"
#include "World.h"
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
/// \brief  Sprite or other 2D surface 
//----------------------------------------------------------------------------------------------------------------------
class Sprite
{
public:
	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma const char* texture file name
	/// \parma float size in X 
	/// \parma float size in Y 
	//----------------------------------------------------------------------------------------------------------------------
	Sprite(const char* textureFile, float x_size, float y_size);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma const char* texture file name
	/// \parma float size in X 
	/// \parma float size in Y 
	/// \parma float height of animation sheet 
	/// \parma float width of animation sheet 
	/// \parma vector<float> animation cycles
	//----------------------------------------------------------------------------------------------------------------------
	Sprite(const char* textureFile, float x_size, float y_size, float& h, float& w, std::vector<float> frameCount);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Constructor
	/// \parma Texture texture
	/// \parma float size in X 
	/// \parma float size in Y 
	/// \parma float height of animation sheet 
	/// \parma float width of animation sheet 
	/// \parma vector<float> animation cycles
	//----------------------------------------------------------------------------------------------------------------------
	Sprite(Texture& texture, float x_size, float y_size, float& h, float& w, std::vector<float> frameCount);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief Destructor
	//----------------------------------------------------------------------------------------------------------------------
	~Sprite();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief draw the sprite
	//----------------------------------------------------------------------------------------------------------------------
	void draw();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief update the sprite
	/// \parma float Delta Time
	//----------------------------------------------------------------------------------------------------------------------
	void update(float dt);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief update the sprite
	/// \parma float Delta Time
	/// \parma math::Mat3 martix
	//----------------------------------------------------------------------------------------------------------------------
	void update(float dt, math::Mat3 matrix);

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief unbind the sprite
	//----------------------------------------------------------------------------------------------------------------------
	void bindSprite();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief unbind the sprite
	//----------------------------------------------------------------------------------------------------------------------
	void unbindSprite();

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the sprite state
	/// \parma int state
	//----------------------------------------------------------------------------------------------------------------------
	inline void state(int s) { m_state = s; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the sprite state
	/// \return int state
	//----------------------------------------------------------------------------------------------------------------------
	inline int getState() { return m_state; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief has the 'sprite' been killed, finished death animation cycle
	/// \return bool
	//----------------------------------------------------------------------------------------------------------------------
	inline bool isDead() { return m_deathComplete; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief get the sprite matrix
	/// \return math::Mat3
	//----------------------------------------------------------------------------------------------------------------------
	inline math::Mat3 matrix() { return m_matrix; }

	//----------------------------------------------------------------------------------------------------------------------
	/// \brief set the sprite matrix
	/// \parma math::Mat3
	//----------------------------------------------------------------------------------------------------------------------
	inline void matrix(math::Mat3 m) { m_matrix = m; }

private:
	Texture* m_texture; ///< sprite/surface texture
	math::Mat3 m_matrix; ///< position
	uint32_t m_vbo; ///< Vertex Buffer Object
	uint32_t m_ibo; ///< IBO
	vertUV m_verts[4]; ///< vertex data
	float m_transition; ///< which image in sprite sheet currnetly on
	float m_totalTransitions; ///< total number of sprite
	int m_lastTransition; ///< last image in sprite sheet use
	float m_uvDividesW; ///< UV X co-ordinates (for using a sprite sheet)
	float m_uvDividesH; ///< UV Y co-ordinates (for using a sprite sheet)
	int m_state; ///< idle/walking/attacking/died etc.
	std::vector<float> m_stateTransitions; ///< switch between the different animation states 
	bool m_deathComplete; ///< completed death animation cycle
	bool loadTextureFromFile; ///< was a texture new and loaded from file or passes in?
};
