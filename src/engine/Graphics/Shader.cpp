#include "Graphics/Shader.hpp"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <print>
#include <sstream>

namespace Reblocked::Engine::Graphics
{
Shader::~Shader()
{
	if (m_programID != 0)
	{
		glDeleteProgram(m_programID);
		m_programID = 0;
	}
}

Shader::Shader(Shader&& other) noexcept
		: m_programID(other.m_programID)
{
	other.m_programID = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
	if (this != &other)
	{
		if (m_programID != 0)
		{
			glDeleteProgram(m_programID);
		}
		m_programID = other.m_programID;
		other.m_programID = 0;
	}
	return *this;
}

bool Shader::loadFromSource(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	GLuint vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	if (vertexShader == 0)
		return false;

	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return false;
	}

	bool success = linkProgram(vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return success;
}

bool Shader::loadFromFiles(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vertexFile(vertexPath);
	if (!vertexFile)
	{
		std::println(stderr, "Failed to open vertex shader: {}", vertexPath);
		return false;
	}
	std::stringstream vertexStream;
	vertexStream << vertexFile.rdbuf();
	std::string vertexSrc = vertexStream.str();

	std::ifstream fragmentFile(fragmentPath);
	if (!fragmentFile)
	{
		std::println(stderr, "Failed to open fragment shader: {}", fragmentPath);
		return false;
	}
	std::stringstream fragmentStream;
	fragmentStream << fragmentFile.rdbuf();
	std::string fragmentSrc = fragmentStream.str();

	return loadFromSource(vertexSrc, fragmentSrc);
}

GLuint Shader::compileShader(const std::string& source, unsigned int type)
{
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::println(stderr, "Shader compilation failed: {}", infoLog);
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

bool Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	GLint success;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(m_programID, 512, nullptr, infoLog);
		std::println(stderr, "Shader linking failed: {}", infoLog);
		glDeleteProgram(m_programID);
		m_programID = 0;
		return false;
	}

	return true;
}

void Shader::use() const { glUseProgram(m_programID); }

void Shader::unbind() const { glUseProgram(0); }

int Shader::getUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(m_programID, name.c_str());
}

void Shader::setUniform(const std::string& name, float value) const
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, int value) const
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
}
