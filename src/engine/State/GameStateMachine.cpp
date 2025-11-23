#include "State/GameStateMachine.hpp"

#include <print>

namespace Reblocked::Engine::State
{
void GameStateMachine::registerState(const std::string& name, StateFactory factory)
{
	m_stateFactories[name] = factory;
	std::println("Registered state: {}", name);
}

void GameStateMachine::transitionTo(const std::string& name)
{
	auto it = m_stateFactories.find(name);
	if (it == m_stateFactories.end())
	{
		std::println(stderr, "State not found: {}", name);
		return;
	}

	if (m_currentState)
	{
		m_currentState->exit();
	}

	m_currentState = it->second();
	m_currentStateName = name;
	m_currentState->enter();

	std::println("Transitioned to state: {}", name);
}

void GameStateMachine::update(float dt)
{
	if (m_currentState)
	{
		m_currentState->update(dt);
	}
}

void GameStateMachine::render(Graphics::Renderer& renderer)
{
	if (m_currentState)
	{
		m_currentState->render(renderer);
	}
}

void GameStateMachine::handleInput(const Core::InputManager& input)
{
	if (m_currentState)
	{
		m_currentState->handleInput(input);
	}
}
}
