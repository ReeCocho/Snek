#include <glm\gtc\matrix_transform.hpp>
#include "Camera.hpp"
#include "Transform.hpp"
#include <iostream>

namespace snk
{
	Camera* Camera::mainCamera = nullptr;

	Camera::Camera(Scene* scene, Entity entity, ComponentID id) : Component(scene, entity, id)
	{
		setRunOnBegin(true);
		setRunOnPreRender(true);
	}

	void Camera::onBegin()
	{
		m_transform = getEntity().getComponent<Transform>();
	}

	void Camera::onPreRender(float deltaTime)
	{
		float aspectRatio = static_cast<float>(Engine::get()->getGraphics()->getWidth()) / static_cast<float>(Engine::get()->getGraphics()->getHeight());

		CameraData data = {};
		data.view = glm::lookAt
		(
			m_transform->getPosition(),
			m_transform->getPosition() + glm::vec3(0, 0, -1),
			glm::vec3(m_transform->getUp(), 0)
		);

		data.projection = glm::ortho
		(
			-aspectRatio * (m_size / 2.0f), 
			aspectRatio * (m_size / 2.0f), 
			-m_size / 2.0f, 
			m_size / 2.0f
		);

		data.mainCamera = this == mainCamera;

		Engine::get()->getRenderer()->drawTo(data);
	}
}