#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace Reblocked
{
class ShaderProgram;
class Camera;
class Mesh;

class Renderer
{
	public:
	Renderer();
	~Renderer();

	bool init();
	void setViewport(int width, int height);
	void clear(const glm::vec4& color);

	void drawMesh(const Mesh& mesh, const glm::mat4& transform);

	Camera& getCamera() { return *m_camera; }
	const Camera& getCamera() const { return *m_camera; }

	private:
	std::unique_ptr<ShaderProgram> m_defaultShader;
	std::unique_ptr<Camera> m_camera;

	glm::ivec2 m_viewportSize { 1280, 720 };
};
}
