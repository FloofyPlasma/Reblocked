#include "Gameplay/CollisionDetector.hpp"
#include "World/Grid.hpp"
#include "World/Piece.hpp"

namespace Reblocked::Game
{

bool CollisionDetector::checkCollision(const Piece& piece, const Grid& grid)
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

bool CollisionDetector::isGrounded(const Piece& piece, const Grid& grid)
{
	Piece testPiece = piece;
	testPiece.move({ 0, 0, -1 });

	return checkCollision(testPiece, grid);
}
}
