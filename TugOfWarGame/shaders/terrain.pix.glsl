#version 330 ///< shader version

uniform sampler2D texture; ///< texture
uniform vec4 ambient; ///< ambient
uniform vec4 diffuse; ///< diffuse

in vec2 pix_uv; ///< uv from vertex shader

out vec4 output_colour; ///< output colour

void main()
{
  // compute ambient term
  vec4 termAmbient = ambient;

  // compute diffuse term
  vec4 termDiffuse = texture2D(texture, pix_uv) * diffuse;


  // output texture
  output_colour = termAmbient + termDiffuse;
}