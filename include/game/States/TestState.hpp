#pragma once

#include "Graphics/Mesh.hpp"
#include "State/GameStateMachine.hpp"

#include <memory>

namespace Reblocked::Game::States
{
class TestState : public Engine::State::GameState
{
	public:
	void enter() override;
	void update(float dt) override;
	void render(Engine::Graphics::Renderer& renderer) override;
	void handleInput(const Engine::Core::InputManager& input) override;

	private:
	std::unique_ptr<Engine::Graphics::Mesh> m_cubeMesh;
	float m_rotation = 0.0f;
};
}
