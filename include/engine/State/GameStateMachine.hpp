#pragma once

#include "Core/InputManager.hpp"
#include "Graphics/Renderer.hpp"

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace Reblocked::Engine::State
{

class GameState
{
	public:
	virtual ~GameState() = default;

	virtual void enter() { }
	virtual void exit() { }
	virtual void update(float dt) = 0;
	virtual void render(Graphics::Renderer& renderer) = 0;
	virtual void handleInput(const Core::InputManager& input) = 0;
};

class GameStateMachine
{
	public:
	GameStateMachine() = default;

	using StateFactory = std::function<std::unique_ptr<GameState>()>;

	void registerState(const std::string& name, StateFactory factory);
	void transitionTo(const std::string& name);

	void update(float dt);
	void render(Graphics::Renderer& renderer);
	void handleInput(const Core::InputManager& input);

	bool hasState() const { return m_currentState != nullptr; }

	private:
	std::unordered_map<std::string, StateFactory> m_stateFactories;
	std::unique_ptr<GameState> m_currentState;
	std::string m_currentStateName;
};
}
