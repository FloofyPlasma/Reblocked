#pragma once

#include <glm/glm.hpp>

namespace Reblocked::Game
{

struct GameRules
{
	glm::ivec3 gridSize { 5, 5, 18 };

	float initialDropInterval = 1.0f;
	float minDropInterval = 0.1f;
	float dropSpeedMultiplier = 0.95f;

	int linesPerLevel = 10;

	int scorePerCell = 10;
	int layerBonus[5] = {
		0,
		100,
		300,
		800,
		2000,
	};

	glm::ivec3 getSpawnPosition() const
	{
		return glm::ivec3 { gridSize.x / 2, gridSize.y / 2, gridSize.z - 3 };
	}

	float getDropInterval(int level) const
	{
		float interval = initialDropInterval;
		for (int i = 1; i < level; ++i)
		{
			interval *= dropSpeedMultiplier;
		}

		return std::max(interval, minDropInterval);
	}
};
}
