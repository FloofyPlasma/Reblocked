#pragma once

#include "Graphics/Camera.hpp"
#include "Graphics/Mesh.hpp"
#include "Graphics/Shader.hpp"

#include <glm/glm.hpp>
#include <memory>

namespace Reblocked::Engine::Graphics
{

class Renderer
{
	public:
	Renderer();
	~Renderer();

	bool init();
	void setViewport(int width, int height);
	void clear(const glm::vec4& color);

	void drawMesh(const Mesh& mesh, const glm::mat4& transform,
			const glm::vec3& color = glm::vec3(1.0f), float alpha = 1.0f);

	Camera& getCamera() { return *m_camera; }
	const Camera& getCamera() const { return *m_camera; }

	private:
	std::unique_ptr<Shader> m_defaultShader;
	std::unique_ptr<Camera> m_camera;

	glm::ivec2 m_viewportSize { 1280, 720 };
};
}
