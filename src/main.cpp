#include "Core/Application.hpp"

// States
#include "States/TestState.hpp"

#include <print>

int main()
{
	Reblocked::Engine::Core::Application app;

	if (!app.init())
	{
		std::println(stderr, "Failed to initialize application");
		return 1;
	}

	auto& stateMachine = app.getStateMachine();

	stateMachine.registerState(
			"test", []() { return std::make_unique<Reblocked::Game::States::TestState>(); });

	stateMachine.transitionTo("test");

	app.run();
	app.shutdown();

	return 0;
}
