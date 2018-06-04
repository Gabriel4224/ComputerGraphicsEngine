#include "Camera.h"

void Camera::SetPerspective(const float FovY, const float AspectRatio, const float NearDistance, const float FarDistance)
{
	m_ProjectionMatrix = glm::perspective(FovY, AspectRatio, NearDistance, FarDistance);
}

void Camera::SetlookAt(const glm::vec3 & FromPosition, const glm::vec3 & ToPosition, const glm::vec3 & YAxis)
{
	m_ViewMatrix = glm::lookAt(FromPosition, ToPosition, YAxis);
	m_worldTransform = glm::inverse(m_ViewMatrix);
	UpdateMatrices();
}

void Camera::setPosition(glm::vec4 position)
{
	m_worldTransform[3] = position;
	m_ViewMatrix = glm::inverse(m_worldTransform);
	UpdateMatrices(); 
}

glm::mat4 Camera::GetWorldTransform() const
{
	return glm::mat4(m_worldTransform);
}

glm::mat4 Camera::GetViewTransform() const
{
	return glm::mat4(m_ViewMatrix);
}

glm::mat4 Camera::GetProjectionTransform() const
{
	return glm::mat4(m_ProjectionMatrix);
}

glm::mat4 Camera::GetProjectionViewTransform() const
{
	return glm::mat4(m_ProjectionXViewMatrix);
}

void Camera::translate(glm::vec4 positonmodifier)
{
	m_worldTransform[3] += positonmodifier; 
}

Camera::Camera()
{
	m_worldTransform = glm::mat4(1.0f);
	m_ViewMatrix = glm::mat4(1.0f);
	m_ProjectionMatrix = glm::mat4(1.0f);
	m_ProjectionXViewMatrix = glm::mat4(1.0f);
}

void Camera::UpdateMatrices()
{
	m_ProjectionXViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

const glm::mat4 & Camera::getProjectionMatrix() const
{
		return ProjectionMatrix;
}

void Camera::SetProjectionMatric(glm::mat4 projectionMatrix)
{
}

glm::vec4 Camera::GetPosition() const
{
	return m_worldTransform[3];
}

glm::vec3 Camera::GetDirection() const
{
	return glm::vec3();
}

glm::vec3 Camera::GetUpVector() const
{
	return glm::vec3();
}
