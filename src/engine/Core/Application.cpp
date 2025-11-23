#include "Core/Application.hpp"

#include <chrono>
#include <memory>
#include <print>

namespace Reblocked::Engine::Core
{
Application::Application() = default;

Application::~Application() { shutdown(); }

bool Application::init()
{
	std::println("Initializing Reblocked...");

	Window::Config windowConfig;
	windowConfig.title = "Reblocked";
	windowConfig.width = 1280;
	windowConfig.height = 720;
	windowConfig.vsync = true;
	windowConfig.resizable = true;
	windowConfig.msaaSamples = 4;

	if (!m_window.init(windowConfig))
	{
		std::println(stderr, "Failed to initialize window");
		return false;
	}

	m_renderer = std::make_unique<Graphics::Renderer>();
	if (!m_renderer->init())
	{
		std::println(stderr, "Failed to initialize renderer");
		return false;
	}

	auto size = m_window.getSize();
	m_renderer->setViewport(size.x, size.y);

	m_input = std::make_unique<InputManager>();
	m_input->setupDefaultBindings();

	m_stateMachine = std::make_unique<State::GameStateMachine>();

	m_initialized = true;
	std::println("Initializing complete");
	return true;
}

void Application::run()
{
	if (!m_initialized)
	{
		std::println(stderr, "Cannot run: Application not initialized");
		return;
	}

	std::println("Starting main loop...");

	using Clock = std::chrono::high_resolution_clock;
	using Duration = std::chrono::duration<float>;

	auto lastTime = Clock::now();

	while (m_window.isRunning())
	{
		auto currentTime = Clock::now();
		float deltaTime = Duration(currentTime - lastTime).count();
		lastTime = currentTime;

		if (deltaTime > 0.25f)
			deltaTime = 0.25f;

		m_window.pollEvents(m_input.get());

		update(deltaTime);

		render();
		m_window.swap();

		m_input->update();
	}
}
void Application::update(float deltaTime)
{
	if (m_input->isActionPressed(GameAction::Quit))
	{
	}

	if (m_stateMachine)
	{
		m_stateMachine->update(deltaTime);
		m_stateMachine->handleInput(*m_input);
	}
}

void Application::render()
{
	m_renderer->clear({ 0.1f, 0.1f, 0.15f, 1.0f });

	if (m_stateMachine)
	{
		m_stateMachine->render(*m_renderer);
	}
}

void Application::shutdown()
{
	if (!m_initialized)
	{
		return;
	}

	std::println("Shutting down...");

	m_stateMachine.reset();
	m_input.reset();
	m_renderer.reset();

	m_initialized = false;
	std::println("Shutdown complete");
}
}
