#pragma once

#include "Core/InputManager.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>

#include <string>

namespace Reblocked::Engine::Core
{

class Window
{
	public:
	struct Config
	{
		std::string title = "Reblocked";
		int width = 1280;
		int height = 720;
		bool vsync = true;
		bool resizable = false;
		int msaaSamples = 4;
	};

	Window() = default;
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) noexcept = default;
	Window& operator=(Window&&) noexcept = default;

	bool init(const Config& config);
	void swap();
	void pollEvents(InputManager* input = nullptr);

	bool isRunning() const { return m_running; };
	glm::ivec2 getSize() const;
	float getAspectRatio() const;

	SDL_Window* getHandle() const { return m_window; }

	private:
	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;

	bool m_running = false;
	glm::ivec2 m_size { 1280, 720 };
};
}
