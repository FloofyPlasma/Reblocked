#pragma once

#include "World/Grid.hpp"
#include "World/Piece.hpp"

namespace Reblocked::Game
{

class CollisionDetector
{
	public:
	static bool checkCollision(const Piece& piece, const Grid& grid);

	static bool isGrounded(const Piece& piece, const Grid& grid);
};
}
