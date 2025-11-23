#include "Core/Application.hpp"

// States
#include "States/PlayingState.hpp"
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
			"test", []() { return std::make_unique<Reblocked::Game::TestState>(); });

	stateMachine.registerState(
			"playing", []() { return std::make_unique<Reblocked::Game::PlayingState>(); });

	stateMachine.transitionTo("playing");

	app.run();
	app.shutdown();

	return 0;
}
