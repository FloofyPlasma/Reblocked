#include "States/TestState.hpp"

#include "Core/InputManager.hpp"
#include "Graphics/MeshBuilder.hpp"
#include "Graphics/Renderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <print>

namespace Reblocked::Game::States
{
void TestState::enter()
{
	std::println("TestState entered");
	m_cubeMesh = Engine::Graphics::MeshBuilder::createCube(1.0f, { 1.0f, 0.5f, 0.2f });
}

void TestState::update(float dt) { m_rotation += dt * 45.0f; }

void TestState::render(Engine::Graphics::Renderer& renderer)
{
	glm::mat4 transform(1.0f);
	transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, glm::radians(m_rotation * 0.5f), glm::vec3(1, 0, 0));

	renderer.drawMesh(*m_cubeMesh, transform);
}

void TestState::handleInput(const Engine::Core::InputManager& input)
{
	if (input.isActionJustPressed(Engine::Core::GameAction::Quit))
	{
		std::println("Quit requested!");
	}
}
}
