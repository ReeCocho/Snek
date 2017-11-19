#include "Engine.hpp"

namespace snk
{
	std::unique_ptr<Engine> Engine::singleton;



	Engine::Engine(const std::string& name, uint32_t width, uint32_t height)
	{
		m_threadPool = std::make_unique<ThreadPool>(1);
		m_input = std::make_unique<Input>();
		m_graphics = std::make_unique<Graphics>(name, width, height);
		m_renderer = std::make_unique<Renderer>(m_graphics.get());
		m_scene = std::make_unique<Scene>();
	}

	Engine::~Engine()
	{
		m_threadPool->wait();

		m_scene = nullptr;
		m_threadPool = nullptr;
		m_renderer = nullptr;
		m_graphics = nullptr;
		m_input = nullptr;
	}

	void Engine::initialize(const std::string& name, uint32_t width, uint32_t height)
	{
		singleton = std::make_unique<Engine>(name, width, height);
	}

	void Engine::start()
	{
		// Variables used for delta time
		uint64_t currentTick = SDL_GetPerformanceCounter();
		uint64_t lastTick = SDL_GetPerformanceCounter();

		while (!singleton->m_input->isClosing())
		{
			// Get input events
			singleton->m_input->pollEvents();

			// Wait for the thread sto finish
			singleton->m_threadPool->wait();

			// Bind the context to the main thread
			singleton->m_graphics->bindMainContext();

			// Calculate delta time
			currentTick = SDL_GetPerformanceCounter();
			float deltaTime = static_cast<float>(currentTick - lastTick) / static_cast<float>(SDL_GetPerformanceFrequency());

			// Perform a tick in the scene
			singleton->m_scene->tick(deltaTime);

			// Rendering
			singleton->m_threadPool->workers[0]->addJob([]() { singleton->m_renderer->render(); });

			// Set the last tick count to the current tick count
			lastTick = currentTick;
		}

		// Wait for the thread sto finish
		singleton->m_threadPool->wait();
	}

	void Engine::stop()
	{
		singleton->m_threadPool->wait();

		singleton->m_scene = nullptr;
		singleton->m_renderer = nullptr;
		singleton->m_graphics = nullptr;
		singleton->m_input = nullptr;

		singleton = nullptr;
	}
}