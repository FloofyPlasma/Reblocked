#pragma once

#include "World/Piece.hpp"

#include <memory>
#include <random>
#include <vector>

namespace Reblocked::Game
{

struct PieceTemplate
{
	std::vector<BlockOffset> blocks;
	uint8_t colorId;
	std::string name;
};

class PieceFactory
{
	public:
	PieceFactory();

	std::unique_ptr<Piece> createRandomPiece();
	std::unique_ptr<Piece> createPiece(int templateIndex);

	size_t getTemplateCount() const { return m_templates.size(); }

	private:
	void initializeTemplates();

	std::vector<PieceTemplate> m_templates;
	std::mt19937 m_rng;
	std::uniform_int_distribution<size_t> m_distribution;
};
}
