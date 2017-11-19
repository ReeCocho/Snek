#include <glm\gtc\type_ptr.hpp>
#include "Renderer.hpp"

namespace snk
{
	Renderer::Renderer(Graphics* graphics) : m_graphics(graphics)
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::render()
	{
		// Bind contex to the current thread
		m_graphics->bindRenderContext();

		// Clear screen
		m_graphics->clearScreen();
		
		// Find the main camera.
		CameraData mainCamera = {};
		for (const auto& camera : m_cameras)
			if (camera.mainCamera)
			{
				mainCamera = camera;
				break;
			}

		// Make sure it's the main camera
		if (!mainCamera.mainCamera)
			return;

		// Calculate VP matrix
		glm::mat4 VP = mainCamera.projection * mainCamera.view;

		// Render every mesh
		for (size_t i = 0; i < m_meshes.size(); i++)
		{
			size_t index = (m_meshes.size() - i) - 1;
			
			m_meshes[index].material->use();
			
			// Set MVP matrix
			GLint mvp = glGetUniformLocation(m_meshes[index].material->getShader()->getProgram(), "MVP");
			glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(VP * m_meshes[index].model));

			glBindVertexArray(m_meshes[index].mesh->getVAO());
			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_meshes[index].mesh->getIndexCount()), GL_UNSIGNED_INT, 0);
		}

		// Swap old screen with new screen
		m_graphics->swapBuffers();

		// Clear queued meshes
		m_meshes.clear();
		m_cameras.clear();
	}
}