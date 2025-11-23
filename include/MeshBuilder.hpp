#pragma once

#include "Mesh.hpp"

#include <memory>

namespace Reblocked
{

class MeshBuilder
{
	public:
	static std::unique_ptr<Mesh> createCube(float size = 1.0f, const glm::vec3& color = { 1, 1, 1 });
	static std::unique_ptr<Mesh> createPlane(
			float width, float depth, const glm::vec3& color = { 0.5f, 0.5f, 0.5f });
};

}
