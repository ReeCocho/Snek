#pragma once

/** 
 * @file Snek.hpp
 * @brief Snek header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <vector>
#include "Engine.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"

namespace snk
{
	/**
	 * @struct NodeData
	 * @brief Information about a node in the map.
	 */
	struct NodeData
	{
		/** Renderer. */
		SpriteRenderer* renderer = nullptr;

		/** Is it a yummy? */
		bool yummy = false;
	};

	/**
	 * @class Snek
	 * @brief Snek game manager.
	 */
	class Snek : public Component
	{
	public:

		/**
		 * @brief Constructor.
		 * @param Scene the component is in.
		 * @param Entity the component belongs to.
		 * @param ID of the type of component.
		 */
		Snek(Scene* scene, Entity entity, ComponentID id);

		/**
		 * @brief Destructor.
		 */
		~Snek() = default;

		/**
		 * @brief Called once per tick.
		 * @param Time in seconds since last tick.
		 */
		virtual void onTick(float deltaTime);

		/**
		 * @brief Initialize snek.
		 * @param Width.
		 * @param Height.
		 */
		void init(size_t w, size_t h);

		/**
		 * @brief Set node.
		 * @param Width.
		 * @param Height.
		 * @param Data
		 */
		void setNode(size_t w, size_t h, const NodeData& node)
		{
			m_nodes[w][h] = node;
		}

		/**
		 * @brief Pick a random spot for the yummy.
		 */
		void pickYummySpot();



		/** Empty material. */
		Material* m_emptyMaterial = nullptr;

		/** Snake material. */
		Material* m_snakeMaterial = nullptr;

		/** Yummy material. */
		Material* m_yummyMaterial = nullptr;

	private:

		/**
		 * @brief Check if a position is in a snek spot.
		 * @param X.
		 * @param Y.
		 */
		bool isSnekSpot(size_t x, size_t y);

		/** Snek pieces. */
		std::vector<glm::vec2> m_snek = {};

		/** Nodes. */
		std::vector<std::vector<NodeData>> m_nodes;

		/** Movement timer. */
		float m_moveTimer = 0;

		/** Movement vector. */
		glm::vec2 m_movement = glm::vec2(1, 0);
	};
}