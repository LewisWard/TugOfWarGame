#version 330 ///< shader version

uniform sampler2D texture; ///< texture
uniform vec4 state; ///< state of the menu 

in vec2 pix_uv; ///< uv from vertex shader

out vec4 ps_colour; ///< output colour

void main()
{
	// output texture
	ps_colour = texture2D(texture, pix_uv) + state;
}