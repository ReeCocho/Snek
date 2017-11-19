#include <iostream>
#include "Shader.hpp"

namespace snk
{
	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// Create vertex shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* v = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &v, NULL);
		glCompileShader(vertexShader);

		// Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* f = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &f, NULL);
		glCompileShader(fragmentShader);

#ifndef NDEBUG
		GLint success = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		std::cout << "Fragment Shader: " << (success == GL_TRUE ? "Pass" : "Fail") << "\n";

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		std::cout << "Vertex Shader: " << (success == GL_TRUE ? "Pass" : "Fail") << "\n";
#endif

		// Create shader program
		m_program = glCreateProgram();
		glAttachShader(m_program, vertexShader);
		glAttachShader(m_program, fragmentShader);

		// Link shaders with the program
		glLinkProgram(m_program);

		// Delete shaders
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		// Cleanup
		glUseProgram(0);
		glDeleteProgram(m_program);
	}
}