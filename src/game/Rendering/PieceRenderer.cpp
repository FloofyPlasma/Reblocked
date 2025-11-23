#include "Rendering/PieceRenderer.hpp"

#include "Graphics/MeshBuilder.hpp"
#include "Graphics/Renderer.hpp"
#include "World/Piece.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Reblocked::Game
{

void PieceRenderer::initialize()
{
	m_cubeMesh = Engine::Graphics::MeshBuilder::createCube(1.0f, { 1, 1, 1 });
}

void PieceRenderer::render(const Piece& piece, Engine::Graphics::Renderer& renderer)
{
	if (!m_cubeMesh)
	{
		return;
	}

	auto worldPositions = piece.getWorldPositions();

	for (const auto& pos : worldPositions)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(pos) + glm::vec3(0.5f));
		transform = glm::scale(transform, glm::vec3(0.95f));

		renderer.drawMesh(*m_cubeMesh, transform);
	}
}
}
