#pragma once

/** 
 * @file Entity.hpp
 * @brief Entity header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include "Scene.hpp"

namespace snk
{
	class Scene;

	typedef size_t ComponentID;

	/**
	 * @class Entity
	 * @brief Allows for interfacing with an entities components.
	 * @see Component
	 */
	class Entity
	{
	public:

		/**
		* @brief Default constructor.
		*/
		Entity() = default;

		/**
		 * @brief Constructor.
		 * @param Scene the entity is in.
		 * @param Entities handle.
		 */
		Entity(Scene* scene, size_t handle);

		/**
		 * @brief Constructor.
		 * @param Scene the entity is in.
		 * @note Will create a new entity in the scene.
		 */
		Entity(Scene* scene);

		/**
		 * @brief Destructor.
		 */
		~Entity() = default;

		/**
		 * @brief Destoy this entity.
		 */
		inline void destroy()
			{
				m_scene->destroy(m_handle);
			}

		/**
		 * @brief Get handle.
		 * @return Handle.
		 */
		inline size_t getHandle() const
			{
				return m_handle;
			}

		/**
		 * @brief Get scene.
		 * @return Scene.
		 */
		inline Scene* getScene()
			{
				return m_scene;
			}

		/**
		 * @brief Get if the entity has a component.
		 * @return If the entity has the component.
		 */
		template<class T>
		bool hasComponent()
			{
				return m_scene->hasComponent<T>(m_handle);
			}

		/**
		 * @brief Get a component on the entity.
		 * @return Point to component.
		 * @note Returns nullptr if the entity doesn't contain the component.
		 */
		template<class T>
		T* getComponent()
			{
				return m_scene->getComponent<T>(m_handle);
			}

		/**
		 * @brief Add a new component to the entity.
		 * @return Pointer to new component.
		 * @note If the entity already contains a component of the same type it will return that instead.
		 */
		template<class T>
		T* addComponent()
			{
				return m_scene->addComponent<T>(m_handle);
			}

		/**
		* @brief Removes a component from the entity.
		*/
		template<class T>
		void removeComponent()
			{
				m_scene->removeComponent<T>(m_handle);
			}

	private:

		/** Scene. */
		Scene* m_scene;

		/** Handle. */
		size_t m_handle;
	};
}