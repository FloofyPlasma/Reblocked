#pragma once

#include <glm/glm.hpp>

namespace Reblocked::Engine::Graphics
{

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;

	Vertex() = default;
	Vertex(
			const glm::vec3& pos, const glm::vec3& norm = { 0, 1, 0 }, const glm::vec3& col = { 1, 1, 1 })
			: position(pos)
			, normal(norm)
			, color(col)
	{
	}
};
}
