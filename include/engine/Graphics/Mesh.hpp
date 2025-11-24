#pragma once

#include "Graphics/Vertex.hpp"

#include <glad/gl.h>
#include <vector>

namespace Reblocked::Engine::Graphics
{

class Mesh
{
	public:
	enum class Primitive : GLenum
	{
		Triangles = GL_TRIANGLES,
		Lines = GL_LINES
	};

	Mesh() = default;
	~Mesh();

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	Mesh& operator=(Mesh&& other) noexcept;

	void setData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	void setPrimitive(Primitive p) { m_primitive = p; }
	void draw() const;

	bool isValid() const { return m_vao != 0; }

	private:
	void cleanup();

	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_ebo = 0;
	size_t m_indexCount = 0;
	Primitive m_primitive = Primitive::Triangles;
};
}
