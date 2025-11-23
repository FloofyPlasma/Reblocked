#include "Graphics/MeshBuilder.hpp"

#include <glm/glm.hpp>

namespace Reblocked::Engine::Graphics
{

std::unique_ptr<Mesh> MeshBuilder::createCube(float size, const glm::vec3& color)
{
	float s = size * 0.5f;

	std::vector<Vertex> vertices = {
		// Front face
		{ { -s, -s, s }, { 0, 0, 1 }, color },
		{ { s, -s, s }, { 0, 0, 1 }, color },
		{ { s, s, s }, { 0, 0, 1 }, color },
		{ { -s, s, s }, { 0, 0, 1 }, color },

		// Back face
		{ { s, -s, -s }, { 0, 0, -1 }, color },
		{ { -s, -s, -s }, { 0, 0, -1 }, color },
		{ { -s, s, -s }, { 0, 0, -1 }, color },
		{ { s, s, -s }, { 0, 0, -1 }, color },

		// Right face
		{ { s, -s, s }, { 1, 0, 0 }, color },
		{ { s, -s, -s }, { 1, 0, 0 }, color },
		{ { s, s, -s }, { 1, 0, 0 }, color },
		{ { s, s, s }, { 1, 0, 0 }, color },

		// Left face
		{ { -s, -s, -s }, { -1, 0, 0 }, color },
		{ { -s, -s, s }, { -1, 0, 0 }, color },
		{ { -s, s, s }, { -1, 0, 0 }, color },
		{ { -s, s, -s }, { -1, 0, 0 }, color },

		// Top face
		{ { -s, s, s }, { 0, 1, 0 }, color },
		{ { s, s, s }, { 0, 1, 0 }, color },
		{ { s, s, -s }, { 0, 1, 0 }, color },
		{ { -s, s, -s }, { 0, 1, 0 }, color },

		// Bottom face
		{ { -s, -s, -s }, { 0, -1, 0 }, color },
		{ { s, -s, -s }, { 0, -1, 0 }, color },
		{ { s, -s, s }, { 0, -1, 0 }, color },
		{ { -s, -s, s }, { 0, -1, 0 }, color },
	};

	std::vector<uint32_t> indices = {
		0,
		1,
		2,
		2,
		3,
		0, // Front
		4,
		5,
		6,
		6,
		7,
		4, // Back
		8,
		9,
		10,
		10,
		11,
		8, // Right
		12,
		13,
		14,
		14,
		15,
		12, // Left
		16,
		17,
		18,
		18,
		19,
		16, // Top
		20,
		21,
		22,
		22,
		23,
		20, // Bottom
	};

	auto mesh = std::make_unique<Mesh>();
	mesh->setData(vertices, indices);
	return mesh;
}

std::unique_ptr<Mesh> MeshBuilder::createPlane(float width, float depth, const glm::vec3& color)
{
	float w = width * 0.5f;
	float d = depth * 0.5f;

	std::vector<Vertex> vertices = {
		{ { -w, 0, -d }, { 0, 1, 0 }, color },
		{ { w, 0, -d }, { 0, 1, 0 }, color },
		{ { w, 0, d }, { 0, 1, 0 }, color },
		{ { -w, 0, d }, { 0, 1, 0 }, color },
	};

	std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

	auto mesh = std::make_unique<Mesh>();
	mesh->setData(vertices, indices);
	return mesh;
}

}
