#include "Core/Window.hpp"

#include <SDL3/SDL_video.h>
#include <glad/gl.h>
#include <print>

namespace Reblocked::Engine::Core
{

Window::~Window()
{
	if (m_glContext)
	{
		SDL_GL_DestroyContext(m_glContext);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	SDL_Quit();
}

bool Window::init(const Config& config)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::println(stderr, "SDL init failed: {}", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	if (config.msaaSamples > 0)
	{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, config.msaaSamples);
	}

	SDL_WindowFlags flags = SDL_WINDOW_OPENGL;
	if (config.resizable)
	{
		flags |= SDL_WINDOW_RESIZABLE;
	}

	m_window = SDL_CreateWindow(config.title.c_str(), config.width, config.height, flags);

	if (!m_window)
	{
		std::println(stderr, "Window creation failed: {}", SDL_GetError());
		return false;
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_glContext)
	{
		std::println(stderr, "OpenGL context creation failed: {}", SDL_GetError());
		return false;
	}

	if (config.vsync)
	{
		if (!SDL_GL_SetSwapInterval(1))
		{
			std::println(stderr, "Warning: VSync not supported");
		}
	}

	int version = gladLoadGL(static_cast<GLADloadfunc>(SDL_GL_GetProcAddress));
	if (version == 0)
	{
		std::println(stderr, "GLAD init failed");
		return false;
	}

	std::println(
			"OpenGL Version {}.{} loaded", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	m_size = { w, h };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	if (config.msaaSamples > 0)
	{
		glEnable(GL_MULTISAMPLE);
	}

	m_running = true;
	return true;
}

void Window::swap() { SDL_GL_SwapWindow(m_window); }

void Window::pollEvents(InputManager* input)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_EVENT_QUIT:
		{
			m_running = false;
		}
		break;

		case SDL_EVENT_WINDOW_RESIZED:
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
		{
			int w, h;
			SDL_GetWindowSize(m_window, &w, &h);
			m_size = { w, h };
			glViewport(0, 0, w, h);
			std::println("Window resized to {}x{}", w, h);
		}
		break;

		case SDL_EVENT_KEY_DOWN:
		{
			if (input)
			{
				input->onKeyDown(e.key.key);
			}
			if (e.key.key == SDLK_ESCAPE)
			{
				m_running = false;
			}
		}
		break;

		case SDL_EVENT_KEY_UP:
		{
			if (input)
			{
				input->onKeyUp(e.key.key);
			}
		}
		break;
		}
	}
}

glm::ivec2 Window::getSize() const { return m_size; }

float Window::getAspectRatio() const
{
	return static_cast<float>(m_size.x) / static_cast<float>(m_size.y);
}

}
