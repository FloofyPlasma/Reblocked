#include "Rendering/GridRenderer.hpp"

#include "Graphics/MeshBuilder.hpp"
#include "Graphics/Vertex.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Reblocked::Game::Rendering
{

GridRenderer::GridRenderer()
{
	m_colorPalette[1] = glm::vec3(1.0f, 0.0f, 0.0f); // Red
	m_colorPalette[2] = glm::vec3(0.0f, 1.0f, 0.0f); // Green
	m_colorPalette[3] = glm::vec3(0.0f, 0.0f, 1.0f); // Blue
	m_colorPalette[4] = glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
	m_colorPalette[5] = glm::vec3(1.0f, 0.0f, 1.0f); // Magenta
	m_colorPalette[6] = glm::vec3(0.0f, 1.0f, 1.0f); // Cyan
	m_colorPalette[7] = glm::vec3(1.0f, 0.5f, 0.0f); // Orange
}

void GridRenderer::initialize()
{
	m_cubeMesh = Engine::Graphics::MeshBuilder::createCube(1.0f, { 1, 1, 1 });
}

void GridRenderer::createWireframeMesh(const glm::ivec3& dimensions)
{
	std::vector<Engine::Graphics::Vertex> vertices;
	std::vector<uint32_t> indices;

	glm::vec3 gray(0.3f, 0.3f, 0.3f);

	for (int x = 0; x <= dimensions.x; ++x)
	{
		for (int y = 0; y <= dimensions.y; ++y)
		{
			uint32_t baseIdx = vertices.size();
			vertices.emplace_back(glm::vec3(x, y, 0), glm::vec3(0, 0, 1), gray);
			vertices.emplace_back(glm::vec3(x, y, dimensions.z), glm::vec3(0, 0, 1), gray);
			indices.push_back(baseIdx);
			indices.push_back(baseIdx + 1);
		}
	}
	for (int x = 0; x <= dimensions.x; ++x)
	{
		uint32_t baseIdx = vertices.size();
		vertices.emplace_back(glm::vec3(x, 0, 0), glm::vec3(0, 1, 0), gray);
		vertices.emplace_back(glm::vec3(x, dimensions.y, 0), glm::vec3(0, 1, 0), gray);
		indices.push_back(baseIdx);
		indices.push_back(baseIdx + 1);
	}

	for (int y = 0; y <= dimensions.y; ++y)
	{
		uint32_t baseIdx = vertices.size();
		vertices.emplace_back(glm::vec3(0, y, 0), glm::vec3(1, 0, 0), gray);
		vertices.emplace_back(glm::vec3(dimensions.x, y, 0), glm::vec3(1, 0, 0), gray);
		indices.push_back(baseIdx);
		indices.push_back(baseIdx + 1);
	}

	m_wireframeMesh = std::make_unique<Engine::Graphics::Mesh>();
	m_wireframeMesh->setData(vertices, indices);
}

void GridRenderer::render(const World::Grid& grid, Engine::Graphics::Renderer& renderer)
{
	if (!m_wireframeMesh)
	{
		createWireframeMesh(grid.getDimensions());
	}

	auto dimensions = grid.getDimensions();

	for (int z = 0; z < dimensions.z; ++z)
	{
		for (int y = 0; y < dimensions.y; ++y)
		{
			for (int x = 0; x < dimensions.x; ++x)
			{
				glm::ivec3 pos { x, y, z };
				uint8_t colorId = grid.getCellColor(pos);

				if (colorId != 0) // Cell is occupied
				{
					glm::mat4 transform(1.0f);
					transform = glm::translate(transform, glm::vec3(pos) + glm::vec3(0.5f));
					transform = glm::scale(transform, glm::vec3(0.95f));
					// TODO: Set color uniform based on colorId
					renderer.drawMesh(*m_cubeMesh, transform);
				}
			}
		}
	}
}

}
