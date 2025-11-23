#pragma once

#include "Window.hpp"

#include <memory>

namespace Reblocked
{
class Renderer;
class InputManager;
class GameStateMachine;

class Application
{
	public:
	Application();
	~Application();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	bool init();
	void run();
	void shutdown();

	GameStateMachine& getStateMachine() { return *m_stateMachine; }
	Renderer& getRenderer() { return *m_renderer; }
	InputManager& getInputManager() { return *m_input; }
	Window& getWindow() { return m_window; }

	private:
	void update(float deltaTime);
	void render();

	Window m_window;

	std::unique_ptr<Renderer> m_renderer;
	std::unique_ptr<InputManager> m_input;
	std::unique_ptr<GameStateMachine> m_stateMachine;

	bool m_initialized = false;
};

}
