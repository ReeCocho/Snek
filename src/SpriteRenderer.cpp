#include "Engine.hpp"
#include "SpriteRenderer.hpp"

namespace snk
{
	SpriteRenderer::SpriteRenderer(Scene* scene, Entity entity, ComponentID id) : Component(scene, entity, id)
	{
		setRunOnBegin(true);
		setRunOnPreRender(true);
	}

	void SpriteRenderer::onBegin()
	{
		m_transform = getEntity().getComponent<Transform>();
	}

	void SpriteRenderer::onPreRender(float deltaTime)
	{
		if (m_mesh && m_material)
		{
			MeshData data = {};
			data.material = m_material;
			data.mesh = m_mesh;
			data.depth = m_depth;
			data.model = m_transform->getModelMatrix();

			Engine::get()->getRenderer()->draw(data);
		}
	}
}