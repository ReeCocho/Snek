#pragma once

/** 
 * @file Engine.hpp
 * @brief Engine header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <memory>
#include <thread>
#include "Input.hpp"
#include "Graphics.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Component.hpp"
#include "ThreadPool.hpp"

namespace snk
{
	/**
	 * @class Engine
	 * @brief Game engine singleton.
	 */
	class Engine
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Engine() = default;

		/**
		 * @brief Constructor.
		 * @param Window name.
		 * @param Window width.
		 * @param Window height.
		 */
		Engine(const std::string& name, uint32_t width, uint32_t height);

		/**
		 * @brief Destructor.
		 */
		~Engine();

		/**
		 * @brief Get singleton.
		 * @return Singleton.
		 */
		static inline Engine* get()
		{
			return singleton.get();
		}

		/**
		 * @brief Initialize engine.
		 * @param Window name.
		 * @param Window width.
		 * @param Window height.
		 */
		static void initialize(const std::string& name, uint32_t width, uint32_t height);

		/**
		 * @brief Start the engine.
		 */
		static void start();

		/** 
		 * @brief Stop the engine.
		 */
		static void stop();

		/**
		 * @brief Get input manager.
		 * @return Input manager.
		 */
		inline Input* getInput()
		{
			return m_input.get();
		}

		/**
		 * @brief Get graphics context.
		 * @return Graphics context.
		 */
		inline Graphics* getGraphics()
		{
			return m_graphics.get();
		}

		/**
		 * @brief Get rendering engine.
		 * @return Rendering engine.
		 */
		inline Renderer* getRenderer()
		{
			return m_renderer.get();
		}

		/**
		 * @brief Get scene manager.
		 * @return Scene manager.
		 */
		inline Scene* getScene()
		{
			return m_scene.get();
		}

	private:

		/** Singleton. */
		static std::unique_ptr<Engine> singleton;

		/** Thread pool. */
		std::unique_ptr<ThreadPool> m_threadPool;

		/** Input manager. */
		std::unique_ptr<Input> m_input;

		/** Graphics context. */
		std::unique_ptr<Graphics> m_graphics;

		/** Rendering engine. */
		std::unique_ptr<Renderer> m_renderer;

		/** Scene manager. */
		std::unique_ptr<Scene> m_scene;
	};
}