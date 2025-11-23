#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>

namespace Reblocked::Game
{

struct BlockOffset
{
	glm::ivec3 offset;

	BlockOffset(int x, int y, int z)
			: offset(x, y, z)
	{
	}
	BlockOffset(glm::ivec3 off)
			: offset(off)
	{
	}
};

class Piece
{
	public:
	Piece(const std::vector<BlockOffset>& blocks, uint8_t colorId);

	void move(const glm::ivec3& delta) { m_position += delta; }
	void setPosition(const glm::ivec3& pos) { m_position = pos; }
	glm::ivec3 getPosition() const { return m_position; }

	void rotateX();
	void rotateY();
	void rotateZ();

	std::vector<glm::ivec3> getWorldPositions() const;

	const std::vector<BlockOffset>& getBlocks() const { return m_blocks; }
	uint8_t getColorId() const { return m_colorId; }
	glm::quat getRotation() const { return m_rotation; }

	private:
	std::vector<BlockOffset> m_blocks;
	glm::ivec3 m_position { 0, 0, 0 };
	glm::quat m_rotation { 1.0f, 0.0f, 0.0f, 0.0f };
	uint8_t m_colorId;
};
}
