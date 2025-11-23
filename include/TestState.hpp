#pragma once

#include "GameStateMachine.hpp"
#include "Mesh.hpp"

#include <memory>

namespace Reblocked
{
class TestState : public GameState
{
	public:
	void enter() override;
	void update(float dt) override;
	void render(Renderer& renderer) override;
	void handleInput(const InputManager& input) override;

	private:
	std::unique_ptr<Mesh> m_cubeMesh;
	float m_rotation = 0.0f;
};
}
