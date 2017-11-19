#pragma once

/** 
 * @file Component.hpp
 * @brief Component header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <vector>
#include <functional>
#include <glm\glm.hpp>
#include "Entity.hpp"

namespace snk
{
	class Scene;

	/**
	 * @typedef ComponentID
	 * @brief ID of a given component.
	 */
	typedef size_t ComponentID;

	/**
	 * @class Component
	 * @brief Describes an aspect of an entity and what it does.
	 */
	class Component
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Component() = default;

		/**
		 * @brief Constructor.
		 * @param Scene the component is in.
		 * @param Entity the component belongs to.
		 * @param ID of the type of component.
		 */
		Component(Scene* scene, Entity entity, ComponentID id);

		/**
		 * @brief Destructor.
		 */
		virtual ~Component() = default;

		/**
		 * @brief Get entity.
		 * @return Entity.
		 */
		inline Entity& getEntity()
		{
			return m_entity;
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
		 * @brief Get components ID.
		 * @return Components ID.
		 */
		inline const size_t getID()
		{
			return m_id;
		}

		/**
		 * @brief Set if the component runs onBegin().
		 * @return If the component runs onBegin().
		 */
		inline const bool setRunOnBegin(bool value)
		{
			m_runOnBegin = value;
			return m_runOnBegin;
		}

		/**
		 * @brief Set if the component runs onTick().
		 * @return If the component runs onTick().
		 */
		inline const bool setRunOnTick(bool value)
		{
			m_runOnTick = value;
			return m_runOnTick;
		}

		/**
		 * @brief Set if the component runs onLateTick().
		 * @return If the component runs onLateTick().
		 */
		inline const bool setRunOnLateTick(bool value)
		{
			m_runOnLateTick = value;
			return m_runOnLateTick;
		}

		/**
		 * @brief Set if the component runs onPreRender().
		 * @return If the component runs onPreRender().
		 */
		inline bool setRunOnPreRender(bool value)
		{
			m_runOnPreRender = value;
			return m_runOnPreRender;
		}

		/**
		 * @brief Set if the component runs onEnd().
		 * @return If the component runs onEnd().
		 */
		inline bool setRunOnEnd(bool value)
		{
			m_runOnEnd = value;
			return m_runOnEnd;
		}

		/**
		 * @brief Get if the component runs onBegin().
		 * @return If the component runs onBegin().
		 */
		inline bool getRunOnBegin() const
		{
			return m_runOnBegin;
		}

		/**
		 * @brief Get if the component runs onTick().
		 * @return If the component runs onTick().
		 */
		inline bool getRunOnTick() const
		{
			return m_runOnTick;
		}

		/**
		 * @brief Get if the component runs onLateTick().
		 * @return If the component runs onLateTick().
		 */
		inline bool getRunOnLateTick() const
		{
			return m_runOnLateTick;
		}

		/**
		 * @brief Get if the component runs onPreRender().
		 * @return If the component runs onPreRender().
		 */
		inline bool getRunOnPreRender() const
		{
			return m_runOnPreRender;
		}


		/**
		 * @brief Get if the component runs onEnd().
		 * @return If the component runs onEnd().
		 */
		inline const bool getRunOnEnd()
		{
			return m_runOnEnd;
		}

		/**
		 * @brief Called when the component is added to a game object.
		 * @note Please use this for memory aquisition.
		 */
		virtual void onBegin();

		/**
		 * @brief Called once per tick.
		 * @param Time in seconds since last tick.
		 */
		virtual void onTick(float deltaTime);

		/**
		 * @brief Called once per tick after onTick().
		 * @param Time in seconds since last tick.
		 */
		virtual void onLateTick(float deltaTime);

		/**
		 * @brief Called once per tick after onLateTick() but before presenting.
		 * @param Time in seconds since last tick.
		 */
		virtual void onPreRender(float deltaTime);

		/**
		 * @brief Called when the component is removed from a game object.
		 * @note Please use this for memory deaquisition.
		 */
		virtual void onEnd();

		/**
		 * @brief Get a unique ID for the given component type.
		 * @return Unique ID for the component.
		 */
		template<class T>
		static ComponentID getUniqueID()
		{
			static ComponentID id{ generateNewID() };
			static std::function<Component*()> constructor = []() { return static_cast<Component*>(new T(nullptr, Entity(nullptr, 0), id)); };

			if (id >= metaData.size())
			{
				MetaData mData = {};
				mData.constructor = constructor;
				metaData.push_back(mData);
			}

			return id;
		}

		/**
		 * @brief Generate unique IDs for the given component types.
		 * @return List of unique IDs for the components.
		 */
		template<class... ComponentTypes>
		static std::vector<ComponentID> getUniqueIDs()
		{
			std::vector<ComponentID> ids = { getUniqueID<ComponentTypes>()... };
			return ids;
		}

		/**
		 * @brief Get components inherited component IDs.
		 * @return Components inherited component IDs.
		 */
		template<class T>
		static const std::vector<ComponentID>& getPolymorphicIDs()
		{
			return metaData[getUniqueID<T>()].children;
		}

		/**
		 * @brief Register a polymorphic relationship between type T1 and T2
		 */
		template<class T1, class T2>
		static void registerPolymorphic()
		{
			auto id1 = getUniqueID<T1>();
			auto isnk = getUniqueID<T2>();

			metaData[id1].children.push_back(isnk);
		}

		/**
		 * @brief Get the number of components registered.
		 * @return Number of registered components.
		 */
		static ComponentID getRegisteredComponentCount();

		/**
		 * @brief Create an instance of a component based on its ID.
		 * @param Scene the component is in.
		 * @param Entity the component is attached to.
		 * @param ID of component.
		 */
		static Component* createComponent(Scene* scene, Entity entity, ComponentID id);

	private:

		/**
		 * @struct MetaData
		 * @brief Meta information about a component
		 */
		struct MetaData
		{
			/** Function pointer to constructor. */
			std::function<Component*()> constructor = nullptr;

			/** Inherited classes. */
			std::vector<ComponentID> children = {};
		};

		/**
		 * @brief Generate a new unique ID.
		 * @return New unique ID.
		 */
		static ComponentID generateNewID();

		/** Number of components registered. */
		static ComponentID componentIDCount;

		/** Every components meta data. */
		static std::vector<MetaData> metaData;

		/**
		 * @brief Creates an instance of a component.
		 * @param Scene the component is in.
		 * @param Game object the component is attached to.
		 * @param The components ID.
		 */
		template<class T>
		static Component* instComponent(Scene* scene, Entity obj, ComponentID id)
		{
			T* component = new T(scene, obj, id);
			return static_cast<Component*>(component);
		}



		/** Scene the component is in. */
		Scene* m_scene;

		/** Component's ID. */
		ComponentID m_id;

		/** Entity the component belongs to. */
		Entity m_entity;

		/** Does the component run onBegin() */
		bool m_runOnBegin = false;

		/** Does the component run onTick() */
		bool m_runOnTick = false;

		/** Does the component run onLateTick() */
		bool m_runOnLateTick = false;

		/** Does the component run onPreRender() */
		bool m_runOnPreRender = false;

		/** Does the component run onEnd() */
		bool m_runOnEnd = false;
	};
}