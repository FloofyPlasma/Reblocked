#pragma once

#include <glad/gl.h>
#include <vector>

#include "Vertex.hpp"

namespace Reblocked
{
class Mesh
{
	public:
	Mesh() = default;
	~Mesh();

	// Delete copy, allow move
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void setData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	void draw() const;

	bool isValid() const { return m_vao != 0; }

	private:
	void cleanup();

	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;
	size_t m_indexCount = 0;
};
}
