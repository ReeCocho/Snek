#pragma once

/** 
 * @file Scene.hpp
 * @brief Scene header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <memory>
#include <vector>

namespace snk
{
	class Transform;

	class Component;

	/**
	 * @class Scene
	 * @brief Manages entities and their components. 
	 */
	class Scene
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Scene();

		/**
		 * @brief Destructor.
		 */
		~Scene();

		/**
		 * @brief Perform a tick in the scene.
		 * @param Delta time.
		 */
		void tick(float deltaTime);



		/**
		 * @brief Create a new entity.
		 * @return New entiy's handle.
		 */
		size_t create();

		/**
		 * @brief Destroy the given entity.
		 * @param Entity handle.
		 * @note Destroys the entity on the next tick.
		 */
		void destroy(size_t entity);

		/**
		 * @brief Get if a entity has a component.
		 * @param Entity to check.
		 * @return If the entity has the component.
		 */
		template<class T>
		bool hasComponent(size_t entityHandle)
		{
			return getComponent<T>(entityHandle) != nullptr;
		}

		/**
		 * @brief Get a component on a entity.
		 * @param Entity to check.
		 * @return Point to component.
		 * @note Returns nullptr if the entity doesn't contain the component.
		 */
		template<class T>
		T* getComponent(size_t entityHandle)
		{
			// Get the unique ID of the given component
			ComponentID uniqueID = Component::getUniqueID<T>();

			// Find the component belonging to the given entity handle
			for (auto& component : m_components[uniqueID])
				if (component->getEntity().getHandle() == entityHandle)
					return static_cast<T*>(component.get());

			// Check for inherited components
			auto inheritedComps = Component::getPolymorphicIDs<T>();
			for (auto inheritedComp : inheritedComps)
				for (auto& component : m_components[inheritedComp])
					if (component->getEntity().getHandle() == entityHandle)
						return static_cast<T*>(component.get());

			return nullptr;
		}

		/**
		 * @brief Add a new component to a entity.
		 * @param Entity of game object to add component to.
		 * @return Pointer to new component.
		 * @note If the entity already contains a component of the same type it will return that instead.
		 */
		template<class T>
		T* addComponent(size_t entityHandle)
		{
			// Get the unique ID of the given component
			ComponentID uniqueID = Component::getUniqueID<T>();

			// Make sure we don't already have the component
			{
				T* comp = getComponent<T>(entityHandle);

				if (comp)
					return comp;
			}

			// Create component
			m_components[uniqueID].push_back(std::make_unique<T>(this, Entity(this, entityHandle), uniqueID));
			auto newComponent = m_components[uniqueID][m_components[uniqueID].size() - 1].get();

			if (newComponent->getRunOnBegin())
				newComponent->onBegin();

			return static_cast<T*>(newComponent);
		}

		/**
		 * @brief Removes a component from a game object.
		 * @param Entity to remove component from.
		 */
		template<class T>
		void removeComponent(size_t entityHandle)
		{
			ComponentID uniqueID = Component::getUniqueID<T>();

			if (!hasComponent<T>(entityHandle) && uniqueID != Component::getUniqueID<Transform>())
				return;

			m_markedComponentsForDelete.push_back(getComponent<T>(entityHandle));
		}

	private:

		/**
		 * @brief Destroy entities marked for delete.
		 */
		void destroyMarkedEntities();

		/**
		 * @brief Destroy components marked for delete.
		 */
		void destroyMarkedComponents();



		/** Component lists ordered by their IDs. */
		std::vector<std::vector<std::unique_ptr<Component>>> m_components;

		/** Components to be deleted. */
		std::vector<Component*> m_markedComponentsForDelete = {};

		/** Entities to be deleted. */
		std::vector<size_t> m_markedEntitiesForDelete = {};

		/** Entity handles that can be reused. */
		std::vector<size_t> m_emptyHandles = {};

		/** Entity handle counter. */
		size_t m_handleCounter = 0;
	};
}