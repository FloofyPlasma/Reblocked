#include "Application.hpp"

// States
#include "TestState.hpp"

#include <print>

int main()
{
	Reblocked::Application app;

	if (!app.init())
	{
		std::println(stderr, "Failed to initialize application");
		return 1;
	}

	auto& stateMachine = app.getStateMachine();

	stateMachine.registerState("test", []() { return std::make_unique<Reblocked::TestState>(); });

	stateMachine.transitionTo("test");

	app.run();
	app.shutdown();

	return 0;
}
