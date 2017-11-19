#include "Entity.hpp"

namespace snk
{
	Entity::Entity(Scene* scene, size_t handle) : m_scene(scene), m_handle(handle)
	{
		
	}

	Entity::Entity(Scene* scene) : m_scene(scene)
	{
		m_handle = m_scene->create();
	}
}