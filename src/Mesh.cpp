#include "Mesh.hpp"

namespace snk
{
	Mesh::Mesh(const std::vector<uint32_t>& indices, const std::vector<glm::vec2>& vertices)
	{
		m_indices = indices;
		m_vertices = vertices;
		m_uvs.resize(vertices.size());

		initialize();
	}

	Mesh::Mesh(const std::vector<uint32_t>& indices, const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& uvs)
	{
		assert(uvs.size() == vertices.size());

		m_indices = indices;
		m_vertices = vertices;
		m_uvs = uvs;

		initialize();
	}

	Mesh::~Mesh()
	{
		// Cleanup
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
		glDeleteVertexArrays(1, &m_vao);
	}

	void Mesh::initialize()
	{
		// Vertex data as an array of floats
		std::vector<float> asFloat(m_vertices.size() * 4);

		for (size_t i = 0; i < m_vertices.size(); i++)
		{
			asFloat[(i * 4) + 0] = m_vertices[i].x;
			asFloat[(i * 4) + 1] = m_vertices[i].y;

			asFloat[(i * 4) + 2] = m_uvs[i].x;
			asFloat[(i * 4) + 3] = m_uvs[i].y;
		}

		// Generate mesh info
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		// Send VBO data
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, asFloat.size() * sizeof(float), asFloat.data(), GL_STATIC_DRAW);

		// Send EBO data
		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t), m_indices.data(), GL_STATIC_DRAW);

		// Define vertex attribute pointers and enable them
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// Unbind our VAO
		glBindVertexArray(0);
	}
}