#include "Snek.hpp"

namespace snk
{
	Snek::Snek(Scene* scene, Entity entity, ComponentID id) : Component(scene, entity, id)
	{
		setRunOnTick(true);
	}

	void Snek::pickYummySpot()
	{
		// Stop the game if there is no place to put a yummy.
		if (m_snek.size() == m_nodes.size() * m_nodes[0].size())
			std::exit(0);

		// Loop until we find a place to put a yummy
		while (true)
		{
			size_t x = static_cast<size_t>(rand() % m_nodes.size());
			size_t y = static_cast<size_t>(rand() % m_nodes[0].size());

			if (isSnekSpot(x, y))
				continue;

			m_nodes[x][y].yummy = true;
			break;
		}
	}

	bool Snek::isSnekSpot(size_t x, size_t y)
	{
		for (const auto snek : m_snek)
			if (snek == glm::vec2(x, y))
				return true;

		return false;
	}

	void Snek::init(size_t w, size_t h)
	{
		m_nodes.clear();
		m_nodes.resize(w);
		for (auto& nodeLine : m_nodes)
			nodeLine.resize(h);

		m_snek.push_back
		(
			glm::vec2
			(
				static_cast<int>(w / 2.0f),
				static_cast<int>(h / 2.0f)
			)
		);
	}

	void Snek::onTick(float deltaTime)
	{
		m_moveTimer += deltaTime;

		// Movement
		{
			float x = Engine::get()->getInput()->getAxis("Horizontal");
			float y = Engine::get()->getInput()->getAxis("Vertical");

			if (m_snek.size() < 2 || m_snek[0] + glm::vec2(x, y) != m_snek[1])
			{
				if (y != 0)
					m_movement = { 0, y };
				else if (x != 0)
					m_movement = { x, 0 };
			}
		}

		// Tick
		if (m_moveTimer >= 0.3f)
		{
			// Reset nodes
			for (size_t x = 0; x < m_nodes.size(); x++)
				for (size_t y = 0; y < m_nodes[x].size(); y++)
					m_nodes[x][y].renderer->setMaterial(m_nodes[x][y].yummy ? m_yummyMaterial : m_emptyMaterial);

			// Move snek
			glm::vec2 newSnekPos = m_snek[0] + m_movement;
			
			// Stop if we run into a wall
			if (newSnekPos.x < 0 || newSnekPos.y < 0 || newSnekPos.x >= m_nodes.size() || newSnekPos.y >= m_nodes[0].size())
				std::exit(0);

			// Stop if we run into ourself
			if (isSnekSpot(static_cast<size_t>(newSnekPos.x), static_cast<size_t>(newSnekPos.y)))
				std::exit(0);

			// Insert snek head
			m_snek.insert(m_snek.begin(), newSnekPos);

			// Eat a yummy
			if (m_nodes[static_cast<size_t>(newSnekPos.x)][static_cast<size_t>(newSnekPos.y)].yummy)
			{
				m_nodes[newSnekPos.x][newSnekPos.y].yummy = false;
				pickYummySpot();
			}
			else
			{
				// Remove the tail
				m_snek.pop_back();
			}

			// Paint snek
			for (const auto snekPiece : m_snek)
			{
				size_t x = static_cast<size_t>(snekPiece.x);
				size_t y = static_cast<size_t>(snekPiece.y);
				m_nodes[x][y].renderer->setMaterial(m_snakeMaterial);
			}

			m_moveTimer = 0;
		}
	}
}