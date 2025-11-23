#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Reblocked
{
Camera::Camera()
{
	updateView();
	updateProjection();
}

void Camera::updateView() { m_viewMatrix = glm::lookAt(m_position, m_target, m_up); }

void Camera::updateProjection()
{
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}
}
