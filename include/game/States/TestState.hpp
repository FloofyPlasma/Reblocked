#pragma once

#include "Rendering/GridRenderer.hpp"
#include "Rendering/PieceRenderer.hpp"
#include "State/GameStateMachine.hpp"
#include "World/Grid.hpp"
#include "World/Piece.hpp"

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
	std::unique_ptr<World::Grid> m_grid;
	std::unique_ptr<World::Piece> m_piece;

	Rendering::GridRenderer m_gridRenderer;
	Rendering::PieceRenderer m_pieceRenderer;

	float m_rotation = 0.0f;
};
}
