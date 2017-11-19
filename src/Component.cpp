#include "Component.hpp"

namespace snk
{
	ComponentID Component::componentIDCount{ 0u };

	std::vector<Component::MetaData> Component::metaData = {};



	Component::Component(Scene* scene, Entity entity, ComponentID id) : m_scene(scene), m_entity(entity), m_id(id)
	{
		
	}

	Component* Component::createComponent(Scene* scene, Entity entity, ComponentID id)
	{
		Component* comp = metaData[id].constructor();
		comp->m_id = id;
		comp->m_scene = scene;
		comp->m_entity = entity;

		return comp;
	}

	ComponentID Component::generateNewID()
	{
		return componentIDCount++;
	}

	ComponentID Component::getRegisteredComponentCount()
	{
		return componentIDCount;
	}

	void Component::onBegin()
	{

	}

	void Component::onTick(float deltaTime)
	{

	}

	void Component::onLateTick(float deltaTime)
	{

	}

	void Component::onPreRender(float deltaTime)
	{

	}

	void Component::onEnd()
	{

	}
}