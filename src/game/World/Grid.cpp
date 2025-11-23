#include "World/Grid.hpp"

namespace Reblocked::Game::World
{

Grid::Grid(glm::ivec3 dimensions)
		: m_dimensions(dimensions)
{
	m_cells.resize(dimensions.x * dimensions.y * dimensions.z, 0);
}

size_t Grid::index(const glm::ivec3& pos) const
{
	return pos.x + pos.y * m_dimensions.x + pos.z * m_dimensions.x * m_dimensions.y;
}

bool Grid::isInBounds(const glm::ivec3& pos) const
{
	return pos.x >= 0 && pos.x < m_dimensions.x && pos.y >= 0 && pos.y < m_dimensions.y && pos.z >= 0
			&& pos.z < m_dimensions.z;
}

bool Grid::isCellOccupied(const glm::ivec3& pos) const
{
	if (!isInBounds(pos))
	{
		return true;
	}
	return m_cells[index(pos)] != 0;
}

void Grid::setCellOccupied(const glm::ivec3& pos, uint8_t colorId)
{
	if (!isInBounds(pos))
		return;
	m_cells[index(pos)] = colorId;
}

void Grid::clearCell(const glm::ivec3& pos)
{
	if (!isInBounds(pos))
		return;
	m_cells[index(pos)] = 0;
}

uint8_t Grid::getCellColor(const glm::ivec3& pos) const
{
	if (!isInBounds(pos))
		return 0;
	return m_cells[index(pos)];
}

bool Grid::isLayerComplete(int z) const
{
	if (z < 0 || z >= m_dimensions.z)
		return false;

	int cellsPerLayer = m_dimensions.x * m_dimensions.y;
	int occupiedCount = 0;

	for (int y = 0; y < m_dimensions.y; ++y)
	{
		for (int x = 0; x < m_dimensions.x; ++x)
		{
			if (isCellOccupied({ x, y, z }))
			{
				occupiedCount++;
			}
		}
	}

	return occupiedCount == cellsPerLayer;
}

std::vector<int> Grid::findCompleteLayers() const
{
	std::vector<int> completeLayers;

	for (int z = 0; z < m_dimensions.z; ++z)
	{
		if (isLayerComplete(z))
		{
			completeLayers.push_back(z);
		}
	}

	return completeLayers;
}

void Grid::clearLayer(int z)
{
	if (z < 0 || z >= m_dimensions.z)
		return;

	for (int y = 0; y < m_dimensions.y; ++y)
	{
		for (int x = 0; x < m_dimensions.x; ++x)
		{
			clearCell({ x, y, z });
		}
	}
}

void Grid::dropLayersAbove(int z)
{
	if (z < 0 || z >= m_dimensions.z - 1)
		return;

	// Move each layer above down by one
	for (int currentZ = z; currentZ < m_dimensions.z - 1; ++currentZ)
	{
		for (int y = 0; y < m_dimensions.y; ++y)
		{
			for (int x = 0; x < m_dimensions.x; ++x)
			{
				glm::ivec3 pos { x, y, currentZ };
				glm::ivec3 above { x, y, currentZ + 1 };

				m_cells[index(pos)] = m_cells[index(above)];
			}
		}
	}

	// Clear the top layer
	clearLayer(m_dimensions.z - 1);
}

void Grid::clear() { std::fill(m_cells.begin(), m_cells.end(), 0); }

}
