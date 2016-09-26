#version 330 ///< shader version

layout(location = 0) in vec4 position; ///< the vertex co-odinate from VBO
layout(location = 1) in vec3 normal; ///< the normal vector from VBO
layout(location = 2) in vec2 uv; ///< the UV co-odinate from VBO

uniform mat4 mvp; ///< Model-View-Projection

out vec2 pix_uv; ///< send uv to fragment shader

void main()
{
	// send uv to fragment shader
	pix_uv = uv;

	// position output
	gl_Position =  mvp * position;
}