#pragma once

#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "World/Grid.hpp"

#include <memory>
#include <unordered_map>

namespace Reblocked::Game::Rendering
{

class GridRenderer
{
	public:
	GridRenderer();

	void initialize();
	void render(const World::Grid& grid, Engine::Graphics::Renderer& renderer);

	private:
	void createWireframeMesh(const glm::ivec3& dimensions);
	void createCubeMesh();
	void updateFilledCells(const World::Grid& grid);

	std::unique_ptr<Engine::Graphics::Mesh> m_wireframeMesh;
	std::unique_ptr<Engine::Graphics::Mesh> m_cubeMesh;

	std::unordered_map<uint8_t, glm::vec3> m_colorPalette;
};
}
