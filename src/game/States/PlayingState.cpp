#include "States/PlayingState.hpp"

#include "Core/InputManager.hpp"
#include "Gameplay/CollisionDetector.hpp"
#include "Graphics/Renderer.hpp"

#include <print>

namespace Reblocked::Game
{

PlayingState::PlayingState() = default;

void PlayingState::enter()
{
	std::println("=== REBLOCKED - Game Start ===");
	std::println("Controls:");
	std::println("  Arrow Keys: Move piece horizontally");
	std::println("  Q/W/E: Rotate on X/Y/Z axes");
	std::println("  Space: Drop piece");
	std::println("  P: Pause (TODO)");
	std::println("  ESC: Quit");
	std::println("");

	m_grid = std::make_unique<Grid>(m_rules.gridSize);

	m_gridRenderer.initialize();
	m_pieceRenderer.initialize();

	m_currentDropInterval = m_rules.getDropInterval(m_level);

	m_nextPiece = m_pieceFactory.createRandomPiece();
	spawnNewPiece();

	std::println("Level: {} | Drop Speed: {:.2f}s", m_level, m_currentDropInterval);
}

void PlayingState::exit()
{
	std::println("=== Game Over ===");
	std::println("Final Score: {}", m_score);
	std::println("Level Reached: {}", m_level);
	std::println("Lines Cleared: {}", m_linesCleared);
	std::println("Pieces Placed: {}", m_totalPiecesPlaced);
}

void PlayingState::spawnNewPiece()
{
	m_currentPiece = std::move(m_nextPiece);

	auto blocks = m_currentPiece->getBlocks();
	glm::ivec3 minOffset(999, 999, 999);
	glm::ivec3 maxOffset(-999, -999, -999);

	for (const auto& block : blocks)
	{
		minOffset = glm::min(minOffset, block.offset);
		maxOffset = glm::max(maxOffset, block.offset);
	}

	glm::ivec3 pieceSize = maxOffset - minOffset + glm::ivec3(1);

	glm::ivec3 spawnPos { (m_rules.gridSize.x - pieceSize.x) / 2 - minOffset.x,
		(m_rules.gridSize.y - pieceSize.y) / 2 - minOffset.y, m_rules.gridSize.z - 1 };

	m_currentPiece->setPosition(spawnPos);

	m_nextPiece = m_pieceFactory.createRandomPiece();
	m_nextPiece->setPosition({ -m_rules.gridSize.x + 2, 1, m_rules.gridSize.z - 5 });

	if (!CollisionDetector::checkCollision(*m_currentPiece, *m_grid))
	{
		return;
	}

	bool foundSpace = false;

	for (int z = spawnPos.z - 1; z >= 0; --z)
	{
		m_currentPiece->setPosition({ spawnPos.x, spawnPos.y, z });

		if (!CollisionDetector::checkCollision(*m_currentPiece, *m_grid))
		{
			foundSpace = true;

			break;
		}
	}

	if (!foundSpace)
	{
		m_gameOver = true;
		std::println("GAME OVER - No space for new piece!");
	}
}

bool PlayingState::tryMovePiece(const glm::ivec3& delta)
{
	glm::ivec3 oldPos = m_currentPiece->getPosition();
	m_currentPiece->move(delta);

	if (CollisionDetector::checkCollision(*m_currentPiece, *m_grid))
	{
		m_currentPiece->setPosition(oldPos);
		return false;
	}

	return true;
}

bool PlayingState::tryRotatePiece(void (Piece::*rotateFunc)())
{
	glm::ivec3 oldPos = m_currentPiece->getPosition();
	glm::quat oldRotation = m_currentPiece->getRotation();

	(m_currentPiece.get()->*rotateFunc)();

	if (CollisionDetector::checkCollision(*m_currentPiece, *m_grid))
	{
		std::vector<glm::ivec3> kicks = {
			{ 1, 0, 0 }, { -1, 0, 0 }, // Left/right
			{ 0, 1, 0 }, { 0, -1, 0 }, // Forward/back
			{ 1, 1, 0 }, { -1, -1, 0 }, // Diagonal
			{ 1, -1, 0 }, { -1, 1, 0 }, { 0, 0, 1 }, { 0, 0, -1 } // Up/down (rare but possible)
		};

		bool kickSucceeded = false;
		for (const auto& kick : kicks)
		{
			m_currentPiece->move(kick);
			if (!CollisionDetector::checkCollision(*m_currentPiece, *m_grid))
			{
				kickSucceeded = true;
				break;
			}
			m_currentPiece->move(-kick);
		}

		if (!kickSucceeded)
		{
			m_currentPiece->setPosition(oldPos);
			m_currentPiece->setRotation(oldRotation);
			return false;
		}
	}

	return true;
}

void PlayingState::lockPiece()
{
	auto worldPositions = m_currentPiece->getWorldPositions();

	for (const auto& pos : worldPositions)
	{
		m_grid->setCellOccupied(pos, m_currentPiece->getColorId());
	}

	m_totalPiecesPlaced++;
	std::println("Piece locked. Total pieces: {}", m_totalPiecesPlaced);

	checkAndClearLayers();

	spawnNewPiece();

	m_dropTimer = 0.0f;
}

void PlayingState::checkAndClearLayers()
{
	auto completeLayers = m_grid->findCompleteLayers();

	if (completeLayers.empty())
	{
		return;
	}

	int layerCount = completeLayers.size();
	std::println("Clearing {} layer(s)!", layerCount);

	// Sort as we want to clear from bottom to top
	std::sort(completeLayers.begin(), completeLayers.end());

	for (int layer : completeLayers)
	{
		m_grid->clearLayer(layer);
	}

	if (!completeLayers.empty())
	{
		int lowestCleared = completeLayers[0];
		for (int i = 0; i < layerCount; ++i)
		{
			m_grid->dropLayersAbove(lowestCleared);
		}
	}

	int cellsCleared = layerCount * (m_rules.gridSize.x * m_rules.gridSize.y);
	int baseScore = cellsCleared * m_rules.scorePerCell;
	int bonus = (layerCount < 5) ? m_rules.layerBonus[layerCount] : m_rules.layerBonus[4];
	m_score += baseScore + bonus;

	m_linesCleared += layerCount;

	std::println("Score: {} (+{} base, +{} bonus)", m_score, baseScore, bonus);

	updateLevel();
}

void PlayingState::updateLevel()
{
	int newLevel = 1 + (m_linesCleared / m_rules.linesPerLevel);

	if (newLevel > m_level)
	{
		m_level = newLevel;
		m_currentDropInterval = m_rules.getDropInterval(m_level);
		std::println("*** LEVEL UP! Now level {} (speed: {:.2f}s) ***", m_level, m_currentDropInterval);
	}
}

void PlayingState::update(float dt)
{
	if (m_gameOver)
	{
		return;
	}

	m_dropTimer += dt;

	if (m_dropTimer >= m_currentDropInterval)
	{
		m_dropTimer = 0.0f;

		if (!tryMovePiece({ 0, 0, -1 }))
		{
			lockPiece();
		}
	}
}

void PlayingState::render(Engine::Graphics::Renderer& renderer)
{
	auto& camera = renderer.getCamera();
	glm::vec3 gridCenter { m_rules.gridSize.x / 2.0f, m_rules.gridSize.y / 2.0f,
		m_rules.gridSize.z / 2.5f };

	float distance = std::max(m_rules.gridSize.x, m_rules.gridSize.y) * 3.0f;
	glm::vec3 cameraPos = gridCenter + glm::vec3(0, 0, distance + 3);

	camera.setPosition(cameraPos);
	camera.lookAt(gridCenter);

	m_gridRenderer.render(*m_grid, renderer);

	if (m_currentPiece && !m_gameOver)
	{
		m_pieceRenderer.render(*m_currentPiece, renderer);
	}

	if (m_nextPiece)
	{
		m_pieceRenderer.render(*m_nextPiece, renderer);
	}

	// TODO: A UI would be nice I guess
}

void PlayingState::handleInput(const Reblocked::Engine::Core::InputManager& input)
{
	if (m_gameOver)
	{
		return;
	}

	using Reblocked::Engine::Core::GameAction;

	// Rotation
	if (input.isActionJustPressed(GameAction::RotateX))
	{
		tryRotatePiece(&Piece::rotateX);
	}
	if (input.isActionJustPressed(GameAction::RotateY))
	{
		tryRotatePiece(&Piece::rotateY);
	}
	if (input.isActionJustPressed(GameAction::RotateZ))
	{
		tryRotatePiece(&Piece::rotateZ);
	}

	// Horizontal movement
	if (input.isActionJustPressed(GameAction::MoveLeft))
	{
		tryMovePiece({ -1, 0, 0 });
	}
	if (input.isActionJustPressed(GameAction::MoveRight))
	{
		tryMovePiece({ 1, 0, 0 });
	}
	if (input.isActionJustPressed(GameAction::MoveForward))
	{
		tryMovePiece({ 0, 1, 0 });
	}
	if (input.isActionJustPressed(GameAction::MoveBack))
	{
		tryMovePiece({ 0, -1, 0 });
	}

	// Drop
	if (input.isActionJustPressed(GameAction::Drop))
	{
		// Fast drop - move down until grounded
		while (tryMovePiece({ 0, 0, -1 }))
		{
			// Keep dropping
		}
		// Lock immediately
		lockPiece();
	}
}
}
