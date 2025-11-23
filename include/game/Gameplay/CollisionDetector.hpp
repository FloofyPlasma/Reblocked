#pragma once

#include "World/Grid.hpp"
#include "World/Piece.hpp"

namespace Reblocked::Game::Gameplay
{

class CollisionDetector
{
	public:
	static bool checkCollision(const World::Piece& piece, const World::Grid& grid);

	static bool isGrounded(const World::Piece& piece, const World::Grid& grid);
};
}
