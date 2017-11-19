#include "Transform.hpp"
#include "Component.hpp"
#include "Scene.hpp"

namespace snk
{
	Scene::Scene()
	{
		// Resize component array to fit every component
		m_components.resize(Component::getRegisteredComponentCount());
	}

	Scene::~Scene()
	{
		// Run onEnd()
		for (auto& componentList : m_components)
			for (auto& component : componentList)
				if (component->getRunOnEnd())
					component->onEnd();
	}

	void Scene::tick(float deltaTime)
	{
		destroyMarkedEntities();
		destroyMarkedComponents();

		// Run onTick()
		for (auto& componentList : m_components)
			for (auto& component : componentList)
				if (component->getRunOnTick())
					component->onTick(deltaTime);

		// Run onLateTick()
		for (auto& componentList : m_components)
			for (auto& component : componentList)
				if (component->getRunOnLateTick())
					component->onLateTick(deltaTime);

		// Run onPreRender()
		for (auto& componentList : m_components)
			for (auto& component : componentList)
				if (component->getRunOnPreRender())
					component->onPreRender(deltaTime);
	}

	size_t Scene::create()
	{
		if (m_emptyHandles.size() > 0)
		{
			size_t handle = m_emptyHandles[0];
			m_emptyHandles.erase(m_emptyHandles.begin());
			addComponent<snk::Transform>(handle);
			return handle;
		}

		auto t = addComponent<snk::Transform>(m_handleCounter++);
		return t->getEntity().getHandle();
	}

	void Scene::destroy(size_t obj)
	{
		m_markedEntitiesForDelete.push_back(obj);
	}

	void Scene::destroyMarkedEntities()
	{
		// Don't bother doing anything if the list is empty
		if (m_markedEntitiesForDelete.size() == 0)
			return;

		// Loop over every component type
		for (size_t i = 0; i < m_components.size(); i++)
			// Loop over every component of type i
			for (size_t j = 0; j < m_components[i].size(); j++)
				// Loop over every entity marked for deletion
				for (size_t k = 0; k < m_markedEntitiesForDelete.size(); k++)
					// If this component belongs the kth marked entity mark it for deletion
					if (m_components[i][j]->getEntity().getHandle() == m_markedEntitiesForDelete[k])
					{
						m_markedComponentsForDelete.push_back(m_components[i][j].get());
						break;
					}

		// Add every marked entity to the empty handle list
		for (size_t i = 0; i < m_markedEntitiesForDelete.size(); i++)
			m_emptyHandles.push_back(m_markedEntitiesForDelete[i]);

		// Empty marked list
		m_markedEntitiesForDelete.clear();
	}

	void Scene::destroyMarkedComponents()
	{
		// Loop over every marked component
		for (auto component : m_markedComponentsForDelete)
			// Loop over every component of "component"s type
			for (size_t j = 0; j < m_components[component->getID()].size(); j++)
				// If the component is the same then destroy it and break
				if (m_components[component->getID()][j].get() == component)
				{
					if (m_components[component->getID()][j]->getRunOnEnd())
						m_components[component->getID()][j]->onEnd();

					m_components[component->getID()].erase(m_components[component->getID()].begin() + j);
					break;
				}

		m_markedComponentsForDelete.clear();
	}
}