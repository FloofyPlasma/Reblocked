#pragma once

#include "Rendering/GridRenderer.hpp"
#include "Rendering/PieceRenderer.hpp"
#include "State/GameStateMachine.hpp"
#include "World/Grid.hpp"
#include "World/Piece.hpp"

#include <memory>

namespace Reblocked::Game
{
class TestState : public Engine::State::GameState
{
	public:
	void enter() override;
	void update(float dt) override;
	void render(Engine::Graphics::Renderer& renderer) override;
	void handleInput(const Engine::Core::InputManager& input) override;

	private:
	bool tryMovePiece(const glm::ivec3& delta);
	bool tryRotatePiece(void (Piece::*rotateFunc)());
	void lockPiece();

	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Piece> m_piece;

	GridRenderer m_gridRenderer;
	PieceRenderer m_pieceRenderer;

	float m_rotation = 0.0f;
};
}
