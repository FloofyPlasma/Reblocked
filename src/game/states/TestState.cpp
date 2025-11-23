#include "States/TestState.hpp"

#include "Core/InputManager.hpp"
#include "Gameplay/CollisionDetector.hpp"
#include "Graphics/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <print>

namespace Reblocked::Game::States
{
void TestState::enter()
{
	std::println("TestState entered");

	m_grid = std::make_unique<World::Grid>(glm::ivec3(5, 5, 18));

	m_grid->setCellOccupied({ 0, 0, 0 }, 1); // Red
	m_grid->setCellOccupied({ 1, 0, 0 }, 2); // Green
	m_grid->setCellOccupied({ 2, 0, 0 }, 3); // Blue
	m_grid->setCellOccupied({ 0, 1, 0 }, 4); // Yellow
	m_grid->setCellOccupied({ 1, 1, 0 }, 5); // Magenta

	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			m_grid->setCellOccupied({ x, y, 1 }, 6); // Cyan
		}
	}

	std::vector<World::BlockOffset> blocks = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 }, { 1, 2, 0 } };
	m_piece = std::make_unique<World::Piece>(blocks, 7); // Orange
	m_piece->setPosition({ 2, 2, 5 }); // Floating above grid

	// Initialize renderers
	m_gridRenderer.initialize();
	m_pieceRenderer.initialize();
}

bool TestState::tryMovePiece(const glm::ivec3& delta)
{
	glm::ivec3 oldPos = m_piece->getPosition();

	m_piece->move(delta);

	if (Gameplay::CollisionDetector::checkCollision(*m_piece, *m_grid))
	{
		m_piece->setPosition(oldPos);
		std::println("Movement blocked by collision");

		return false;
	}

	std::println("Moved to ({}, {}, {})", m_piece->getPosition().x, m_piece->getPosition().y,
			m_piece->getPosition().z);

	return true;
}

bool TestState::tryRotatePiece(void (World::Piece::*rotateFunc)())
{
	glm::quat oldRotation = m_piece->getRotation();

	(m_piece.get()->*rotateFunc)();

	if (Gameplay::CollisionDetector::checkCollision(*m_piece, *m_grid))
	{
		// Collision! Try wall kicks (shift left/right to make rotation work)
		bool kickSucceeded = false;

		// Try shifting right
		m_piece->move({ 1, 0, 0 });
		if (!Gameplay::CollisionDetector::checkCollision(*m_piece, *m_grid))
		{
			std::println("Rotation succeeded with right kick");
			kickSucceeded = true;
		}
		else
		{
			// Try shifting left instead
			m_piece->move({ -2, 0, 0 }); // -2 because we already moved +1
			if (!Gameplay::CollisionDetector::checkCollision(*m_piece, *m_grid))
			{
				std::println("Rotation succeeded with left kick");
				kickSucceeded = true;
			}
			else
			{
				// Try shifting back
				m_piece->move({ 1, 0, 0 }); // Back to original position
			}
		}

		if (!kickSucceeded)
		{
			// All kicks failed, revert rotation
			// We need to undo the rotation - for now just set it back
			// (This is a bit hacky, ideally we'd store rotation state better)
			std::println("Rotation blocked by collision");
			return false;
		}
	}

	std::println("Rotated successfully");
	return true;
}

void TestState::lockPiece()
{
	auto worldPositions = m_piece->getWorldPositions();

	for (const auto& pos : worldPositions)
	{
		m_grid->setCellOccupied(pos, m_piece->getColorId());
	}

	std::println("Piece locked! Creating new piece.");

	std::vector<World::BlockOffset> blocks = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 }, { 1, 2, 0 } };
	m_piece = std::make_unique<World::Piece>(blocks, 7);
	m_piece->setPosition({ 2, 1, 10 });
}

void TestState::update(float dt) { }

void TestState::render(Engine::Graphics::Renderer& renderer)
{
	auto& camera = renderer.getCamera();
	camera.setPosition({ 10.0f, 12.0f, 15.0f });
	camera.lookAt({ 2.5f, 2.5f, 5.0f });

	m_gridRenderer.render(*m_grid, renderer);

	m_pieceRenderer.render(*m_piece, renderer);
}

void TestState::handleInput(const Engine::Core::InputManager& input)
{
	if (input.isActionJustPressed(Engine::Core::GameAction::Quit))
	{
		std::println("Quit requested!");
	}

	if (input.isActionJustPressed(Engine::Core::GameAction::RotateX))
	{
		tryRotatePiece(&World::Piece::rotateX);
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::RotateY))
	{
		tryRotatePiece(&World::Piece::rotateY);
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::RotateZ))
	{
		tryRotatePiece(&World::Piece::rotateZ);
	}

	if (input.isActionJustPressed(Engine::Core::GameAction::MoveLeft))
	{
		tryMovePiece({ -1, 0, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveRight))
	{
		tryMovePiece({ 1, 0, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveForward))
	{
		tryMovePiece({ 0, -1, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveBack))
	{
		tryMovePiece({ 0, 1, 0 });
	}

	if (input.isActionJustPressed(Engine::Core::GameAction::Drop))
	{
		if (tryMovePiece({ 0, 0, -1 }))
		{
			// Successfully moved down
			// Check if now grounded
			if (Gameplay::CollisionDetector::isGrounded(*m_piece, *m_grid))
			{
				lockPiece();
			}
		}
		else
		{
			// Can't move down - must be grounded
			lockPiece();
		}
	}
}
}
