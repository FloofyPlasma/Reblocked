#pragma once

#include "Core/InputManager.hpp"
#include "Gameplay/GameRules.hpp"
#include "Graphics/Renderer.hpp"
#include "Rendering/GridRenderer.hpp"
#include "Rendering/PieceRenderer.hpp"
#include "State/GameStateMachine.hpp"
#include "World/Grid.hpp"
#include "World/Piece.hpp"
#include "World/PieceFactory.hpp"

#include <memory>

namespace Reblocked::Game
{

class PlayingState : public Engine::State::GameState
{
	public:
	PlayingState();

	void enter() override;
	void exit() override;
	void update(float dt) override;
	void render(Engine::Graphics::Renderer& renderer) override;
	void handleInput(const Engine::Core::InputManager& input) override;

	private:
	bool tryMovePiece(const glm::ivec3& delta);
	bool tryRotatePiece(void (Piece::*rotateFunc)());
	void lockPiece();
	void spawnNewPiece();

	void checkAndClearLayers();
	void updateLevel();
	bool isGameOver();

	std::unique_ptr<Grid> m_grid;
	std::unique_ptr<Piece> m_currentPiece;
	std::unique_ptr<Piece> m_nextPiece;
	PieceFactory m_pieceFactory;
	GameRules m_rules;
	;

	float m_dropTimer = 0.0f;
	float m_currentDropInterval = 1.0f;

	int m_score = 0;
	int m_level = 1;
	int m_linesCleared = 0;
	int m_totalPiecesPlaced = 0;

	GridRenderer m_gridRenderer;
	PieceRenderer m_pieceRenderer;

	bool m_gameOver = false;
	bool m_checkGameOver = false;
	float m_gameOverDelay = 0.0f;
};
}
