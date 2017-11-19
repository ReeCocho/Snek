#pragma once

/** 
 * @file Graphics.hpp
 * @brief Graphics header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes. */
#include <SDL.h>
#include <glad\glad.h>
#include <string>

namespace snk
{
	/**
	 * @class Graphics
	 * @brief Manages the window and setup of OpenGL.
	 */
	class Graphics
	{
	public:

		/**
		 * @brief Default constructor.
		 */
		Graphics() = default;

		/**
		 * @brief Constructor.
		 * @param Window name.
		 * @param Width.
		 * @param Height.
		 */
		Graphics(const std::string& name, uint32_t width, uint32_t height);

		/**
		 * @brief Destructor.
		 */
		~Graphics();

		/**
		 * @brief Get window width.
		 * @return Window width.
		 */
		inline uint32_t getWidth() const
		{
			return m_width;
		}

		/**
		 * @brief Get window height.
		 * @return Window heighht.
		 */
		inline uint32_t getHeight() const
		{
			return m_height;
		}

		/**
		 * @brief Set window dimensions.
		 * @param New width.
		 * @param New height.
		 */
		inline void setDimensions(uint32_t width, uint32_t height)
		{
			m_width = width;
			m_height = height;

			SDL_SetWindowSize
			(
				m_window, 
				static_cast<int>(m_width), 
				static_cast<int>(m_height)
			);
		}

		/**
		 * @brief Clear screen buffer.
		 * @note Used internally. Do not call.
		 */
		inline void clearScreen()
		{	
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		/**
		 * @brief Swap screen buffers.
		 * @note Used internally. Do not call.
		 */
		inline void swapBuffers()
		{
			SDL_GL_SwapWindow(m_window);
		}

		/**
		 * @brief Bind rendering context to current thread.
		 */
		void bindRenderContext()
		{
			SDL_GL_MakeCurrent(m_window, m_glContext);
		}

		/**
		 * @brief Bind main context to current thread.
		 */	
		void bindMainContext()
		{
			SDL_GL_MakeCurrent(m_window, NULL);
		}

	private:

		/** Window object. */
		SDL_Window* m_window;

		/** SDL OpenGL rendering context. */
		SDL_GLContext m_glContext;

		/** Window width. */
		uint32_t m_width;

		/** Window height. */
		uint32_t m_height;
	};
}