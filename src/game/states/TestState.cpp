#include "States/TestState.hpp"

#include "Core/InputManager.hpp"
#include "Graphics/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <print>

namespace Reblocked::Game::States
{
void TestState::enter()
{
	std::println("TestState entered");

	m_grid = std::make_unique<World::Grid>(glm::ivec3(5, 5, 18));

	m_grid->setCellOccupied({ 0, 0, 0 }, 1); // Red
	m_grid->setCellOccupied({ 1, 0, 0 }, 2); // Green
	m_grid->setCellOccupied({ 2, 0, 0 }, 3); // Blue
	m_grid->setCellOccupied({ 0, 1, 0 }, 4); // Yellow
	m_grid->setCellOccupied({ 1, 1, 0 }, 5); // Magenta

	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			m_grid->setCellOccupied({ x, y, 1 }, 6); // Cyan
		}
	}

	std::vector<World::BlockOffset> blocks = { { 0, 0, 0 }, { 0, 1, 0 }, { 0, 2, 0 }, { 1, 2, 0 } };
	m_piece = std::make_unique<World::Piece>(blocks, 7); // Orange
	m_piece->setPosition({ 2, 2, 5 }); // Floating above grid

	// Initialize renderers
	m_gridRenderer.initialize();
	m_pieceRenderer.initialize();
}

void TestState::update(float dt)
{
	m_rotation += dt * 30.0f;

	if (static_cast<int>(m_rotation) % 90 == 0 && static_cast<int>(m_rotation) != 0)
	{
		int rotation = static_cast<int>(m_rotation);
		if (rotation % 270 == 0)
		{
			m_piece->rotateZ();
		}
		else if (rotation % 180 == 0)
		{
			m_piece->rotateY();
		}
		else if (rotation % 90 == 0)
		{
			m_piece->rotateX();
		}
	}
}

void TestState::render(Engine::Graphics::Renderer& renderer)
{
	auto& camera = renderer.getCamera();
	camera.setPosition({ 10.0f, 12.0f, 15.0f });
	camera.lookAt({ 2.5f, 2.5f, 5.0f });

	m_gridRenderer.render(*m_grid, renderer);

	m_pieceRenderer.render(*m_piece, renderer);
}

void TestState::handleInput(const Engine::Core::InputManager& input)
{
	if (input.isActionJustPressed(Engine::Core::GameAction::Quit))
	{
		std::println("Quit requested!");
	}

	if (input.isActionJustPressed(Engine::Core::GameAction::RotateX))
	{
		m_piece->rotateX();
		std::println("Rotated X");
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::RotateY))
	{
		m_piece->rotateY();
		std::println("Rotated Y");
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::RotateZ))
	{
		m_piece->rotateZ();
		std::println("Rotated Z");
	}

	if (input.isActionJustPressed(Engine::Core::GameAction::MoveLeft))
	{
		m_piece->move({ -1, 0, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveRight))
	{
		m_piece->move({ 1, 0, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveForward))
	{
		m_piece->move({ 0, -1, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::MoveBack))
	{
		m_piece->move({ 0, 1, 0 });
	}
	if (input.isActionJustPressed(Engine::Core::GameAction::Drop))
	{
		m_piece->move({ 0, 0, -1 });
	}
}
}
