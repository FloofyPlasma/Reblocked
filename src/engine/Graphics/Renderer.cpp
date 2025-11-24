#include "Graphics/Renderer.hpp"

#include "Graphics/DefaultShaders.hpp"

#include <glad/gl.h>
#include <print>

namespace Reblocked::Engine::Graphics
{
Renderer::Renderer() = default;
Renderer::~Renderer() = default;

bool Renderer::init()
{
	std::println("Initializing renderer");

	m_defaultShader = std::make_unique<Shader>();
	if (!m_defaultShader->loadFromSource(Shaders::BasicVertexShader, Shaders::BasicFragmentShader))
	{
		std::println(stderr, "Failed tp load default shader");
		return false;
	}

	m_camera = std::make_unique<Camera>();
	m_camera->setPosition({ 0.0f, 5.0f, 10.0f });
	m_camera->lookAt({ 0.0f, 0.0f, 0.0f });

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	std::println("Renderer initialized");
	return true;
}

void Renderer::setViewport(int width, int height)
{
	m_viewportSize = { width, height };
	glViewport(0, 0, width, height);

	float aspect = static_cast<float>(width) / static_cast<float>(height);
}

void Renderer::clear(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawMesh(
		const Mesh& mesh, const glm::mat4& transform, const glm::vec3& color, float alpha)
{
	if (!mesh.isValid() || !m_defaultShader->isValid())
	{
		return;
	}

	m_defaultShader->use();

	m_defaultShader->setUniform("uModel", transform);
	m_defaultShader->setUniform("uView", m_camera->getViewMatrix());
	m_defaultShader->setUniform("uProjection", m_camera->getProjectionMatrix());
	m_defaultShader->setUniform("uViewPos", m_camera->getPosition());
	m_defaultShader->setUniform("uObjectColor", color);
	m_defaultShader->setUniform("uAlpha", alpha);

	if (alpha < 1.0f)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	mesh.draw();

	if (alpha < 1.0f)
	{
		glDisable(GL_BLEND);
	}

	m_defaultShader->unbind();
}
}
