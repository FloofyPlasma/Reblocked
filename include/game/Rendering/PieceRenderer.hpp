#pragma once

#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "World/Piece.hpp"

#include <memory>

namespace Reblocked::Game::Rendering
{

class PieceRenderer
{
	public:
	void initialize();
	void render(const World::Piece&, Engine::Graphics::Renderer& renderer);

	private:
	std::unique_ptr<Engine::Graphics::Mesh> m_cubeMesh;
};
}
