#include "Graphics.hpp"

namespace snk
{
	Graphics::Graphics(const std::string& name, uint32_t width, uint32_t height) : m_width(width), m_height(height)
	{
		// Initialize SDL video
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("SDL: Unable to initialize video.");

		if (SDL_GL_LoadLibrary(NULL) != 0)
			throw std::runtime_error("SDL: Unable to initialize OpenGL.");

		// Request an OpenGL 3.3 context (should be core)
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		// Also request a depth buffer
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		// Create SDL window
		m_window = SDL_CreateWindow
		(
			name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
		);

		// Check window creation
		if (m_window == nullptr)
			throw std::runtime_error("SDL: Unable to create window.");

		// Share data between threads
		SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);

		// Create OpenGL contexts
		m_glContext = SDL_GL_CreateContext(m_window);

		// Check for context creation
		if (m_glContext == nullptr)
			throw std::runtime_error("SDL: Unable to create OpenGL context.");

		// Initialize GLAD
		gladLoadGLLoader(SDL_GL_GetProcAddress);

		// Use v-sync
		SDL_GL_SetSwapInterval(1);

		// Disable depth test and face culling.
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		// Enable transparency
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Setup some defaults
		glViewport(0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	Graphics::~Graphics()
	{
		SDL_GL_DeleteContext(m_glContext);
		SDL_DestroyWindow(m_window);
	}
}