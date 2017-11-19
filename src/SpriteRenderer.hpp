#pragma once

/** 
 * @file SpriteRenderer.hpp
 * @brief Sprite renderer header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include "Component.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "Transform.hpp"

namespace snk
{
	class SpriteRenderer : public Component
	{
	public:

		/**
		 * @brief Constructor.
		 * @param Scene the component is in.
		 * @param Entity the component belongs to.
		 * @param ID of the type of component.
		 */
		SpriteRenderer(Scene* scene, Entity entity, ComponentID id);

		/**
		 * @brief Destructor.
		 */
		~SpriteRenderer() = default;

		/**
		 * @brief Called when the component is added to a game object.
		 * @note Please use this for memory aquisition.
		 */
		void onBegin() override;

		/**
		 * @brief Called once per tick after onLateTick() but before presenting.
		 * @param Time in seconds since last tick.
		 */
		void onPreRender(float deltaTime) override;

		/**
		 * @brief Set depth.
		 * @param New depth.
		 * @return New depth.
		 */
		inline uint32_t setDepth(uint32_t depth)
		{
			m_depth = depth;
			return m_depth;
		}

		/**
		 * @brief Set mesh.
		 * @param New mesh.
		 * @return New mesh.
		 */
		inline Mesh* setMesh(Mesh* mesh)
		{
			m_mesh = mesh;
			return m_mesh;
		}

		/**
		 * @brief Set material.
		 * @param New material.
		 * @return New material.
		 */
		inline Material* setMaterial(Material* material)
		{
			m_material = material;
			return m_material;
		}

		/**
		 * @brief Get depth.
		 * @return Depth.
		 */
		inline uint32_t getDepth() const
		{
			return m_depth;
		}

		/**
		 * @brief Get mesh.
		 * @return Mesh.
		 */
		inline Mesh* getMesh() const
		{
			return m_mesh;
		}

		/**
		 * @brief Get material.
		 * @return Material.
		 */
		inline Material* getMaterial() const
		{
			return m_material;
		}

	private:

		/** Meshes transform. */
		Transform* m_transform = nullptr;

		/** Mesh to render. */
		Mesh* m_mesh = nullptr;

		/** Material to render the mesh with. */
		Material* m_material = nullptr;

		/** Mesh depth. */
		uint32_t m_depth = 0;
	};
}