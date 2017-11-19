#pragma once

/** 
 * @file Shader.hpp
 * @brief Shader header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <string>
#include <glad\glad.h>

namespace snk
{
	/**
	 * @class Shader
	 * @brief Describes how a mesh looks.
	 */
	class Shader
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Shader() = default;

		/**
		 * @brief Constructor.
		 * @param Vertex shader source.
		 * @param Fragment shader source.
		 */
		Shader(const std::string& vertexSource, const std::string& fragmentSource);

		/**
		 * @brief Destructor.
		 */
		~Shader();

		/**
		 * @brief Get shader program.
		 * @return Shader program.
		 */
		inline GLuint getProgram() const
		{
			return m_program;
		}

	private:

		/** Shader program. */
		GLuint m_program;
	};
}