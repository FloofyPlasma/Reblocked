#include "Rendering/PieceRenderer.hpp"

#include "Graphics/MeshBuilder.hpp"
#include "Graphics/Renderer.hpp"
#include "World/Piece.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Reblocked::Game
{

namespace
{
	static const std::unordered_map<uint8_t, glm::vec3> colorPalette = {
		{ 1, glm::vec3(1.0f, 0.0f, 0.0f) }, // Red
		{ 2, glm::vec3(0.0f, 1.0f, 0.0f) }, // Green
		{ 3, glm::vec3(0.0f, 0.0f, 1.0f) }, // Blue
		{ 4, glm::vec3(1.0f, 1.0f, 0.0f) }, // Yellow
		{ 5, glm::vec3(1.0f, 0.0f, 1.0f) }, // Magenta
		{ 6, glm::vec3(0.0f, 1.0f, 1.0f) }, // Cyan
		{ 7, glm::vec3(1.0f, 0.5f, 0.0f) }, // Orange
	};

}

void PieceRenderer::initialize()
{
	m_cubeMesh = Engine::Graphics::MeshBuilder::createCube(1.0f, { 1, 1, 1 });
}

void PieceRenderer::render(const Piece& piece, Engine::Graphics::Renderer& renderer, float alpha)
{
	if (!m_cubeMesh)
	{
		return;
	}

	auto worldPositions = piece.getWorldPositions();

	glm::vec3 color(1.0f);
	auto it = colorPalette.find(piece.getColorId());
	if (it != colorPalette.end())
	{
		color = it->second;
	}

	for (const auto& pos : worldPositions)
	{
		glm::mat4 transform(1.0f);
		transform = glm::translate(transform, glm::vec3(pos) + glm::vec3(0.5f));
		transform = glm::scale(transform, glm::vec3(0.95f));

		renderer.drawMesh(*m_cubeMesh, transform, color, alpha);
	}
}
}
