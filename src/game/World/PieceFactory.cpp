#include "World/PieceFactory.hpp"

#include <random>

namespace Reblocked::Game
{

PieceFactory::PieceFactory()
		: m_rng(std::random_device {}())
{
	initializeTemplates();
	m_distribution = std::uniform_int_distribution<size_t>(0, m_templates.size() - 1);
}

void PieceFactory::initializeTemplates()
{
	// Flat 2x2
	m_templates.push_back({ { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 } },
			1, // Red
			"Square" });

	// Flat 1x3 line
	m_templates.push_back({ { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 } },
			2, // Green
			"Line3" });

	// Flat 1x4 line
	m_templates.push_back({ { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 }, { 0, 3, 0 } },
			3, // Blue
			"Line4" });

	// L-shape (flat)
	m_templates.push_back({ { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 }, { 1, 2, 0 } },
			4, // Yellow
			"L-Shape" });

	// T-shape (flat)
	m_templates.push_back({ { { 0, 0, 0 }, { 1, 0, 0 }, { 2, 0, 0 }, { 1, 1, 0 } },
			5, // Magenta
			"T-Shape" });

	// Z-shape (flat)
	m_templates.push_back({ { { 0, 0, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 2, 1, 0 } },
			6, // Cyan
			"Z-Shape" });

	// 3D L-corner
	m_templates.push_back({ { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
			7, // Orange
			"3D Corner" });

	// Small cube 2x2x2
	m_templates.push_back({ { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 }, { 0, 0, 1 },
															{ 1, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } },
			1, // Red
			"Cube" });
}

std::unique_ptr<Piece> PieceFactory::createRandomPiece()
{
	size_t index = m_distribution(m_rng);
	return createPiece(index);
}

std::unique_ptr<Piece> PieceFactory::createPiece(int templateIndex)
{
	if (templateIndex < 0 || templateIndex >= static_cast<int>(m_templates.size()))
	{
		templateIndex = 0;
	}

	const auto& templ = m_templates[templateIndex];

	return std::make_unique<Piece>(templ.blocks, templ.colorId);
}

}
