#pragma once

#include "Graphics/Mesh.hpp"
#include "Graphics/Renderer.hpp"
#include "World/Piece.hpp"

#include <memory>

namespace Reblocked::Game
{

class PieceRenderer
{
	public:
	void initialize();
	void render(const Piece&, Engine::Graphics::Renderer& renderer, float alpha = 1.0f);

	private:
	std::unique_ptr<Engine::Graphics::Mesh> m_cubeMesh;
};
}
