#pragma once

/** 
 * @file Renderer.hpp
 * @brief Renderer header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include "Graphics.hpp"
#include "Material.hpp"
#include "Mesh.hpp"

namespace snk
{
	/**
	 * @struct MeshData
	 * @brief Holds data about a mesh to be rendered.
	 */
	struct MeshData
	{
		/** Mesh. */
		Mesh* mesh = nullptr;

		/** Material. */
		Material* material = nullptr;

		/** Model matrix. */
		glm::mat4 model = {};

		/** Mesh depth. */
		uint32_t depth = 0;
	};

	/**
	 * @struct CameraData
	 * @brief Holds data about a camera to render with.
	 */
	struct CameraData
	{
		/** View matrix. */
		glm::mat4 view = {};

		/** Projection matrix. */
		glm::mat4 projection = {};

		/** Is this the camera to render to the screen with? */
		bool mainCamera = false;
	};

	/**
	 * @class Renderer
	 * @brief Rendering engine.
	 */
	class Renderer
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Renderer() = default;

		/**
		 * @brief Constructor.
		 * @param Graphics context.
		 */
		Renderer(Graphics* graphics);

		/**
		 * @brief Destructor.
		 */
		~Renderer();

		/**
		 * @brief Get graphics context.
		 * @return Graphics context.
		 */
		inline Graphics* getGraphics() const
		{
			return m_graphics;
		}

		/**
		 * @brief Render everything to the screen.
		 */
		void render();

		/**
		 * @brief Draw a mesh.
		 * @param Mesh to draw.
		 */
		inline void draw(const MeshData& mesh)
		{
			if(m_meshes.size() == 0)
				m_meshes.push_back(mesh);

			for (size_t i = 0; i < m_meshes.size(); i++)
				if (m_meshes[i].depth <= mesh.depth || i == m_meshes.size() - 1)
				{
					m_meshes.insert(m_meshes.begin() + i, mesh);
					return;
				}
		}

		/**
		 * @brief Draw to a camera.
		 * @param Camera to draw to.
		 */
		inline void drawTo(const CameraData& camera)
		{
			m_cameras.push_back(camera);
		}

	private:

		/** Graphics context. */
		Graphics* m_graphics;

		/** Lists of meshes to render. */
		std::vector<MeshData> m_meshes = {};

		/** List of cameras to render with. */
		std::vector<CameraData> m_cameras = {};
	};
}