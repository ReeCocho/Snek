#include <algorithm>
#include <glm\gtc\matrix_transform.hpp>
#include "Transform.hpp"

namespace snk
{
	Transform::Transform(Scene* scene, Entity entity, ComponentID id) : Component(scene, entity, id)
	{
		m_parent = nullptr;
		generateModelMatrix();
	}

	Transform::~Transform()
	{

	}



	glm::vec3 Transform::setPosition(glm::vec3 value)
	{
		m_position = value;

		if (m_parent == nullptr)
			m_localPosition = m_position;
		else
		{
			glm::vec4 newPos = glm::inverse(m_parent->m_modelMatrix) * glm::vec4(m_position.x, m_position.y, m_position.z, 1.0);
			m_localPosition = glm::vec3(newPos.x, newPos.y, newPos.z);
		}

		generateModelMatrix();
		updateChildren();

		return m_position;
	}

	glm::vec3 Transform::setLocalPosition(glm::vec3 value)
	{
		m_localPosition = value;

		if (m_parent == nullptr)
			m_position = value;
		else
		{
			glm::vec4 newPos = m_parent->m_modelMatrix * glm::vec4(m_localPosition.x, m_localPosition.y, m_localPosition.z, 1.0);
			m_position = glm::vec3(newPos.x, newPos.y, newPos.z);
		}

		generateModelMatrix();
		updateChildren();

		return m_localPosition;
	}

	float Transform::setRotation(float value)
	{
		m_rotation = value;

		if (m_parent == nullptr)
			m_localRotation = m_rotation;
		else
			m_localRotation = m_rotation - m_parent->m_rotation;

		generateModelMatrix();
		updateChildren();

		return m_rotation;
	}

	float Transform::setLocalRotation(float value)
	{
		m_localRotation = value;

		if (m_parent == nullptr)
			m_rotation = m_localRotation;
		else
			m_rotation = m_parent->m_rotation + m_localRotation;

		generateModelMatrix();
		updateChildren();

		return m_localRotation;
	}

	glm::vec2 Transform::setLocalScale(glm::vec2 value)
	{
		m_localScale = value;
		generateModelMatrix();
		updateChildren();
		return m_localScale;
	}

	Transform* Transform::setParent(Transform* parent)
	{
		// Remove self from parents child list
		if (m_parent != nullptr)
			parent->m_children.erase(std::remove(parent->m_children.begin(), parent->m_children.end(), this), parent->m_children.end());

		// Set parent
		m_parent = parent;

		// Add self to new parents children list
		if (m_parent != nullptr)
			parent->m_children.push_back(this);

		// Update local values and model matrix
		setPosition(getPosition());
		setRotation(getRotation());

		return m_parent;
	}



	void Transform::generateModelMatrix()
	{
		m_modelMatrix = {};
		m_unscaledModelMatrix = {};

		// Translation matrix
		m_modelMatrix = glm::translate(m_modelMatrix, m_localPosition);

		// Rotation matrix
		m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_localRotation), glm::vec3(0, 0, 1));
		m_unscaledModelMatrix = m_modelMatrix;

		// Scale matrix
		m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_localScale, 1));

		// Get parent matrix if we have one
		if (m_parent != nullptr)
		{
			m_modelMatrix = m_parent->m_unscaledModelMatrix * m_modelMatrix;
			m_unscaledModelMatrix = m_parent->m_unscaledModelMatrix * m_unscaledModelMatrix;
		}

		// Update childrens model matrix
		for (auto child : m_children)
			child->generateModelMatrix();
	}

	void Transform::updateChildren()
	{
		for (auto child : m_children)
		{
			// Local position to global position
			child->setLocalPosition(child->m_localPosition);

			// Local euler angles to global euler angles
			child->setLocalRotation(child->m_localRotation);

			child->generateModelMatrix();
			child->updateChildren();
		}
	}
}