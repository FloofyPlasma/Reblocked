#include "World/Piece.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace Reblocked::Game
{

Piece::Piece(const std::vector<BlockOffset>& blocks, uint8_t colorId)
		: m_blocks(blocks)
		, m_colorId(colorId)
{
}

void Piece::rotateX()
{
	glm::quat rot = glm::angleAxis(glm::radians(90.0f), glm::vec3(1, 0, 0));
	m_rotation = rot * m_rotation;
}

void Piece::rotateY()
{
	glm::quat rot = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0));
	m_rotation = rot * m_rotation;
}

void Piece::rotateZ()
{
	glm::quat rot = glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 0, 1));
	m_rotation = rot * m_rotation;
}

std::vector<glm::ivec3> Piece::getWorldPositions() const
{
	std::vector<glm::ivec3> worldPositions;
	worldPositions.reserve(m_blocks.size());

	for (const auto& block : m_blocks)
	{
		glm::vec3 rotated = m_rotation * glm::vec3(block.offset);

		glm::ivec3 snapped {
			static_cast<int>(std::round(rotated.x)),
			static_cast<int>(std::round(rotated.y)),
			static_cast<int>(std::round(rotated.z)),
		};

		worldPositions.push_back(m_position + snapped);
	}

	return worldPositions;
}
}
