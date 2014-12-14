// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#include "gl/Program.h"

gls::Program::~Program()
{
	glDeleteProgram(m_program);
	glError("Program::~Program");
}
bool gls::Program::create(const Shader* const vertex, const Shader* const fragment)
{
	// delete program, make sure that there isn't any previous programs'
	if(m_program)
	{
		glDeleteProgram(m_program);
		glError("Program::create");
	}

	// create new program
	m_program = glCreateProgram();
	// check for errors
	glError("Program::create");

	// attach the shaders to the program
	glAttachShader(m_program, vertex->shader());
	glAttachShader(m_program, fragment->shader());
	glError("Program::create");

	// link the program (connects vertex and fragment shaders together)
	glLinkProgram(m_program);
	glError("Program::create");

	// check that linking was good
	int32_t linked = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
	glError("Program::create");

	// will print the error of were the linking failed
	if(linked == GL_FALSE)
	{
		glError("Program::create");
		// what went wrong?
		GLsizei length = 0;
		char linkBuffer[1024]; 
    glGetProgramInfoLog(m_program, 1024, &length, linkBuffer);
    glError("Program::create");
		// print to console
		std::cout<<"Program linking failed: "<<linkBuffer<<std::endl;
		// delete program
		glDeleteProgram(m_program);
		glError("Program::create");
		m_program = 0;
		// return that linking failed
		return false;
	}
	return true;
}
void gls::Program::bind() const
{
	// bind the program for use
	glUseProgram(m_program);
}
void gls::Program::unbind() const
{
	// stop using the program
	glUseProgram(0);
}
