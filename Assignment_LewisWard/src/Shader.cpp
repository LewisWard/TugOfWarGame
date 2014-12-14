// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 14/12/2014
#include "gl/Shader.h"

namespace gls
{
void glError(const char* file)
{
	// get the gl error and print it to console
	switch(glGetError())
	{
	case GL_NO_ERROR: break;
	case GL_INVALID_ENUM: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_INVALID_ENUM\n"; break;
	case GL_INVALID_VALUE: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_INVALID_VALUE\n"; break;
	case GL_INVALID_OPERATION: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_INVALID_OPERATION\n"; break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_INVALID_FRAMEBUFFER_OPERATION\n"; break;
	case GL_OUT_OF_MEMORY: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_OUT_OF_MEMORY\n"; break;
	case GL_STACK_UNDERFLOW: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_STACK_UNDERFLOW\n"; break;
	case GL_STACK_OVERFLOW: std::cout<<"SHADER NAME: "<<file<<" ERROR: GL_STACK_OVERFLOW\n"; break;
	}
}

Shader::Shader(const char* shaderFile, shaderType type)
{
	// open file and create shader source code
	const char* shaderSourceCode = loadShaderFile(shaderFile);

	// make sure we dont have a bad point!
	if(shaderSourceCode)
	{
		// get the name of the file
		m_filename = shaderFile;

		// what type of shader is it?
		switch(type)
		{
		case sVERTEX: m_shader = glCreateShader(GL_VERTEX_SHADER); break;
		case sFRAGMENT: m_shader = glCreateShader(GL_FRAGMENT_SHADER); break;
		}
		// check for an error with the shader
		glError(shaderFile);

		// if shader was created
		if(m_shader)
		{
			// set the shader source to the shader object and check for error
			glShaderSource(m_shader, 1, &shaderSourceCode, NULL);
			glError(shaderFile);
			// compile the shader and check for error
			glCompileShader(m_shader);
			glError(shaderSourceCode);

			// we query the compiled shader for errors
			int32_t shaderCompiled = 0;
			glGetShaderiv(m_shader, GL_COMPILE_STATUS, &shaderCompiled);
			glError(shaderFile);

			// if something failed then error printed
			GLsizei length = 0;
			char errorBuffer[256] = {0};
			glGetShaderInfoLog(m_shader, 256, &length, errorBuffer);
			// print to console
			std::cout<<errorBuffer<<std::endl;

			// shader source code
			m_source = shaderSourceCode;

			// if failed to compile then delete shader
			if(!shaderCompiled)
			{
				glDeleteShader(m_shader);
				glError(shaderFile);
				std::cout<<"\nVertex shader compile failed\n";
				m_shader = 0;
				m_source = "\0";
			}
		}
	}
	else
	{
		std::cout<<"Bad pointer for: shaderSourceCode\n";
	}
}
Shader::~Shader()
{
	// delete shader
	glDeleteShader(m_shader);
}
const char* Shader::shaderSource() const
{
	// return source
	return m_source.c_str();
}
char* Shader::loadShaderFile(const char* shaderFilename)
{
	// file pointer to open file for reading
	std::FILE* file = std::fopen(shaderFilename, "rb");
	// if there is a file
	if(file)
	{
		// go to the end of the file
		if(!std::fseek(file, 0, SEEK_END))
		{
			// get how big the file is 
			size_t fileSize = std::ftell(file);
			if(fileSize)
			{
				// go back to the start of the file
				if(!std::fseek(file, 0, SEEK_SET))
				{
					// allocate new memory for the size of the file
					char* fileData = new char[fileSize + 1];
					// read the file contents 
					std::fread(fileData, fileSize, 1, file);
					// end the string with a '\0' to terminate
					fileData[fileSize] = 0;
					// close the file
					std::fclose(file);
					// return the file/string
					return fileData;
				}
			}
		}
		// close the file
		std::fclose(file);
	}
	// failed
	return 0;
}
};
