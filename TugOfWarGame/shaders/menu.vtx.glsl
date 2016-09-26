#version 330 ///< shader version

layout(location = 0) in vec4 vs_position; ///< the vertex co-odinate from VBO
layout(location = 1) in vec2 vs_uv; ///< the UV co-odinate from VBO

out vec2 pix_uv; ///< send uv to fragment shader

void main()
{
	// send uv to fragment shader
	pix_uv = vs_uv;

	gl_Position = vs_position;
}