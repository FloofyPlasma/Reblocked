#include "Mesh.hpp"

#include <glad/gl.h>

namespace Reblocked
{

Mesh::~Mesh() { cleanup(); }

Mesh::Mesh(Mesh&& other) noexcept
		: m_vao(other.m_vao)
		, m_vbo(other.m_vbo)
		, m_ebo(other.m_ebo)
		, m_indexCount(other.m_indexCount)
{
	other.m_vao = 0;
	other.m_vbo = 0;
	other.m_ebo = 0;
	other.m_indexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
	if (this != &other)
	{
		cleanup();

		m_vao = other.m_vao;
		m_vbo = other.m_vbo;
		m_ebo = other.m_ebo;
		m_indexCount = other.m_indexCount;

		other.m_vao = 0;
		other.m_vbo = 0;
		other.m_ebo = 0;
		other.m_indexCount = 0;
	}
	return *this;
}

void Mesh::cleanup()
{
	if (m_ebo != 0)
	{
		glDeleteBuffers(1, &m_ebo);
		m_ebo = 0;
	}
	if (m_vbo != 0)
	{
		glDeleteBuffers(1, &m_vbo);
		m_vbo = 0;
	}
	if (m_vao != 0)
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
}

void Mesh::setData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
	cleanup();

	m_indexCount = indices.size();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
			0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);
}

void Mesh::draw() const
{
	if (m_vao == 0)
	{
		return;
	}

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indexCount), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
}
