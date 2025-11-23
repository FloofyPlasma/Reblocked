#pragma once

#include "Core/InputManager.hpp"
#include "Core/Window.hpp"
#include "Graphics/Renderer.hpp"
#include "State/GameStateMachine.hpp"

#include <memory>

namespace Reblocked::Engine::Core
{

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

	State::GameStateMachine& getStateMachine() { return *m_stateMachine; }
	Graphics::Renderer& getRenderer() { return *m_renderer; }
	InputManager& getInputManager() { return *m_input; }
	Window& getWindow() { return m_window; }

	private:
	void update(float deltaTime);
	void render();

	Window m_window;

	std::unique_ptr<Graphics::Renderer> m_renderer;
	std::unique_ptr<Core::InputManager> m_input;
	std::unique_ptr<State::GameStateMachine> m_stateMachine;

	bool m_initialized = false;
};
}
