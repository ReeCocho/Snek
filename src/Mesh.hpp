#pragma once

/**
 * @file Mesh.hpp
 * @brief Mesh header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <vector>
#include <glm\glm.hpp>
#include <glad\glad.h>

namespace snk
{
	/**
	 * @class Mesh
	 * @brief Holds data about a renderable mesh.
	 */
	class Mesh
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Mesh() = default;

		/**
		 * @brief Constructor.
		 * @param Indices.
		 * @param Vertices.
		 */
		Mesh(const std::vector<uint32_t>& indices, const std::vector<glm::vec2>& vertices);

		/**
		 * @brief Constructor.
		 * @param Indices.
		 * @param Vertices.
		 * @param UVs.
		 */
		Mesh(const std::vector<uint32_t>& indices, const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& uvs);

		/**
		 * @brief Destructor.
		 */
		~Mesh();

		/**
		 * @brief Get index count.
		 * @return Index count.
		 */
		inline size_t getIndexCount() const
		{
			return m_indices.size();
		}

		/**
		 * @brief Get vertex attribute object.
		 * @return Vertex attribute object.
		 */
		inline GLuint getVAO() const
		{
			return m_vao;
		}

	private:

		/**
		 * @brief Creates the VAO, VBO, and EBO of the mesh.
		 * @note Does no cleanup, so make sure make sure the
		 *		 existing objects are already destroyed.
		 */
		void initialize();



		/** Vertex attribute object. */
		GLuint m_vao = 0;

		/** Vertex buffer object. */
		GLuint m_vbo = 0;

		/** Element buffer object. */
		GLuint m_ebo = 0;

		/** Vertices. */
		std::vector<glm::vec2> m_vertices = {};

		/** UVs. */
		std::vector<glm::vec2> m_uvs = {};

		/** Indices. */
		std::vector<uint32_t> m_indices{};
	};
}