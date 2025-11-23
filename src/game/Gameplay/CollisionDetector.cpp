#include "Gameplay/CollisionDetector.hpp"
#include "World/Grid.hpp"
#include "World/Piece.hpp"

namespace Reblocked::Game::Gameplay
{

bool CollisionDetector::checkCollision(const World::Piece& piece, const World::Grid& grid)
{
	auto worldPositions = piece.getWorldPositions();

	for (const auto& pos : worldPositions)
	{
		if (!grid.isInBounds(pos))
		{
			return true;
		}

		if (grid.isCellOccupied(pos))
		{
			return true;
		}
	}

	return false;
}

bool CollisionDetector::isGrounded(const World::Piece& piece, const World::Grid& grid)
{
	World::Piece testPiece = piece;
	testPiece.move({ 0, 0, -1 });

	return checkCollision(testPiece, grid);
}
}
