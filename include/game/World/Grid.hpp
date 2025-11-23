#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace Reblocked::Game
{

class Grid
{
	public:
	Grid(glm::ivec3 dimensions = { 5, 5, 18 });

	bool isCellOccupied(const glm::ivec3& pos) const;
	void setCellOccupied(const glm::ivec3& pos, uint8_t colorId);
	void clearCell(const glm::ivec3& pos);
	uint8_t getCellColor(const glm::ivec3& pos) const;

	bool isLayerComplete(int z) const;
	std::vector<int> findCompleteLayers() const;
	void clearLayer(int z);
	void dropLayersAbove(int z);
	bool isInBounds(const glm::ivec3& pos) const;
	glm::ivec3 getDimensions() const { return m_dimensions; }

	void clear();
	const std::vector<uint8_t>& getCells() const { return m_cells; }

	private:
	std::size_t index(const glm::ivec3& pos) const;

	glm::ivec3 m_dimensions;
	std::vector<uint8_t> m_cells;
};
}
