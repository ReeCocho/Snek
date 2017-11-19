#pragma once

/**
 * @file Transform.hpp
 * @brief Transform header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include "Component.hpp"

namespace snk
{
	/**
	 * @class Transform
	 * @brief Describes the location in space of a game object.
	 */
	class Transform : public Component
	{
	public:

		/**
		 * @brief Constructor.
		 * @param Scene the component is in.
		 * @param Entity the component belongs to.
		 * @param ID of the type of component.
		 */
		Transform(Scene* scene, Entity entity, ComponentID id);

		/**
		 * @brief Destructor.
		 */
		~Transform();

		/**
		 * @brief Get the transforms position.
		 * @return Position.
		 */
		inline glm::vec3 getPosition() const
		{
			return m_position;
		}

		/**
		 * @brief Get the transform local position.
		 * @return Local position.
		 */
		inline glm::vec3 getLocalPosition() const
		{
			return m_localPosition;
		}

		/**
		 * @brief Get the transforms rotation.
		 * @return Rotation.
		 */
		inline float getRotation() const
		{
			return m_rotation;
		}

		/**
		 * @brief Get the transforms local rotation.
		 * @return Local rotation.
		 */
		inline float getLocalRotation() const
		{
			return m_localRotation;
		}

		/**
		 * @brief Get the transforms local scale.
		 * @return Local scale.
		 */
		inline glm::vec2 getLocalScale() const
		{
			return m_localScale;
		}

		/**
		 * @brief Get the transforms model matrix.
		 * @return Model matrix.
		 */
		inline glm::mat4 getModelMatrix() const
		{
			return m_modelMatrix;
		}

		/**
		 * @brief Get a up std::vector realative to the transform.
		 * @return Up std::vector.
		 */
		inline glm::vec2 getUp() const
		{
			float x = glm::sin(glm::radians(m_rotation));
			float y = glm::cos(glm::radians(m_rotation));
			return glm::vec2(x, y);
		}

		/**
		 * @brief Get a right std::vector realative to the transform.
		 * @return Right std::vector.
		 */
		inline glm::vec2 getRight() const
		{
			float x = glm::cos(glm::radians(m_rotation));
			float y = glm::sin(glm::radians(m_rotation));
			return glm::vec2(x, y);
		}

		/**
		 * @brief Get the transforms parent.
		 * @return Transforms parent.
		 */
		inline Transform* getParent() const
		{
			return m_parent;
		}

		/**
		 * @brief Get the transforms Nth child.
		 * @return Nth child.
		 * @note Returns nullptr if n is out of bounds.
		 */
		inline Transform* getChild(size_t n) const
		{
			assert(n >= 0 && n < m_children.size());
			return m_children[n];
		}

		/**
		 * @brief Get the number of children the transform contains.
		 * @return Number of children.
		 */
		inline size_t childCount() const
		{
			return m_children.size();
		}



		/**
		 * @brief Set the transforms position.
		 * @param New position.
		 * @return New position.
		 */
		glm::vec3 setPosition(glm::vec3 value);

		/**
		 * @brief Set the transforms local position.
		 * @param New local position.
		 * @return New local position.
		 */
		glm::vec3 setLocalPosition(glm::vec3 value);

		/**
		 * @brief Set the transforms rotation.
		 * @param New rotation.
		 * @return New rotation.
		 */
		float setRotation(float value);

		/**
		 * @brief Set the transforms local rotation.
		 * @param New local rotation.
		 * @return New local rotation.
		 */
		float setLocalRotation(float value);

		/**
		 * @brief Set the transforms local scale.
		 * @param New local scale.
		 * @return New local scale.
		 */
		glm::vec2 setLocalScale(glm::vec2 value);

		/**
		 * @brief Set the transforms parent.
		 * @param New parent transform.
		 * @return New parent transform.
		 */
		Transform* setParent(Transform* parent);


		/**
		 * @brief Add the position dispalcement to the old position.
		 * @param Position displacement.
		 * @return New position.
		 */
		inline glm::vec3 modPosition(glm::vec3 value)
		{
			return setPosition(m_position + value);
		}

		/**
		 * @brief Add the local position dispalcement to the old local position.
		 * @param Local position displacement.
		 * @return New local position.
		 */
		inline glm::vec3 modLocalPosition(glm::vec3 value)
		{
			return setLocalPosition(m_localPosition + value);
		}

		/**
		 * @brief Add the rotation dispalcement by the old rotation.
		 * @param Rotation displacement.
		 * @return New rotation.
		 */
		inline float modRotation(float value)
		{
			return setRotation(m_rotation + value);
		}

		/**
		 * @brief Add the local rotation dispalcement by the old local rotation.
		 * @param Local rotation displacement.
		 * @return New local rotation.
		 */
		inline float modLocalRotation(float value)
		{
			return setLocalRotation(m_localRotation + value);
		}

		/**
		 * @brief Add the local scale dispalcement to the old local scale.
		 * @param Local scale displacement.
		 * @return New local scale.
		 */
		inline glm::vec2 modLocalScale(glm::vec2 value)
		{
			return setLocalScale(m_localScale + value);
		}

		/**
		 * @brief Add a new child to the transform.
		 * @param Transform component of the new child.
		 */
		inline Transform* addChild(Transform* obj)
		{
			obj->setParent(this);
			return obj;
		}

	private:

		/**
		 * @brief Generate a new model matrix.
		 */
		void generateModelMatrix();

		/**
		 * @brief Update the transforms children.
		 */
		void updateChildren();

		/** Postion. */
		glm::vec3 m_position = glm::vec3();

		/** Local position. */
		glm::vec3 m_localPosition = glm::vec3();

		/** Local scale. */
		glm::vec2 m_localScale = glm::vec2(1, 1);

		/** Rotation. */
		float m_rotation = 0;

		/** Local rotation. */
		float m_localRotation = 0;

		/** Model matrix. */
		glm::mat4 m_modelMatrix = glm::mat4();

		/** Model matrix without scale applied (Used for hierarchy) */
		glm::mat4 m_unscaledModelMatrix = glm::mat4();

		/** Parent. */
		Transform* m_parent = nullptr;

		/** Children. */
		std::vector<Transform*> m_children = {};
	};
}