#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace Reblocked
{
class Renderer;
class InputManager;

class GameState
{
	public:
	virtual ~GameState() = default;

	virtual void enter() { }
	virtual void exit() { }
	virtual void update(float dt) = 0;
	virtual void render(Renderer& renderer) = 0;
	virtual void handleInput(const InputManager& input) = 0;
};

class GameStateMachine
{
	public:
	GameStateMachine() = default;

	using StateFactory = std::function<std::unique_ptr<GameState>()>;

	void registerState(const std::string& name, StateFactory factory);
	void transitionTo(const std::string& name);

	void update(float dt);
	void render(Renderer& renderer);
	void handleInput(const InputManager& input);

	bool hasState() const { return m_currentState != nullptr; }

	private:
	std::unordered_map<std::string, StateFactory> m_stateFactories;
	std::unique_ptr<GameState> m_currentState;
	std::string m_currentStateName;
};
}
