#pragma once

#include <glm/glm.hpp>

namespace Reblocked::Engine::Graphics
{

class Camera
{
	public:
	Camera();

	void setPosition(const glm::vec3& pos)
	{
		m_position = pos;
		updateView();
	}
	void setTarget(const glm::vec3& target)
	{
		m_target = target;
		updateView();
	}
	void lookAt(const glm::vec3& target) { setTarget(target); }

	void setFov(float fov)
	{
		m_fov = fov;
		updateProjection();
	}
	void setAspectRatio(float aspect)
	{
		m_aspectRatio = aspect;
		updateProjection();
	}
	void setNearFar(float near, float far)
	{
		m_near = near;
		m_far = far;
		updateProjection();
	}

	glm::vec3 getPosition() const { return m_position; }
	glm::mat4 getViewMatrix() const { return m_viewMatrix; }
	glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }
	glm::mat4 getViewProjectionMatrix() const { return m_projectionMatrix * m_viewMatrix; }

	private:
	void updateView();
	void updateProjection();

	glm::vec3 m_position { 0.0f, 0.0f, 10.0f };
	glm::vec3 m_target { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_up { 0.0f, 1.0f, 0.0f };

	float m_fov = 45.0f;
	float m_aspectRatio = 16.0f / 9.0f;
	float m_near = 0.1f;
	float m_far = 100.0f;

	glm::mat4 m_viewMatrix { 1.0f };
	glm::mat4 m_projectionMatrix { 1.0f };
};
}
