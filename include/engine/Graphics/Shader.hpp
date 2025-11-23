#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>

namespace Reblocked::Engine::Graphics
{

class Shader
{
	public:
	Shader() = default;
	~Shader();

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other) noexcept;

	bool loadFromSource(const std::string& vertexSrc, const std::string& fragmentSrc);
	bool loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath);

	void use() const;
	void unbind() const;

	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, const glm::vec2& value) const;
	void setUniform(const std::string& name, const glm::vec3& value) const;
	void setUniform(const std::string& name, const glm::vec4& value) const;
	void setUniform(const std::string& name, const glm::mat3& value) const;
	void setUniform(const std::string& name, const glm::mat4& value) const;

	GLuint getID() const { return m_programID; }
	bool isValid() const { return m_programID != 0; }

	private:
	GLuint compileShader(const std::string& source, unsigned int type);
	bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
	int getUniformLocation(const std::string& name) const;

	GLuint m_programID = 0;
};
}
