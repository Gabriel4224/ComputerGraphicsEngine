#include "Camera.h"

void Camera::setPosition(glm::vec4 position)
{
	m_worldTransform[3] = position;
}

void Camera::translate(glm::vec4 positonmodifier)
{
	m_worldTransform[3] += positonmodifier; 
}

const glm::mat4 & Camera::getProjectionMatrix() const
{
	// TODO: insert return statement here
	//assert(m_hasSetProjectionMatric == true)
	//{
		return ProjectionMatrix;
	//}
}

void Camera::SetProjectionMatric(glm::mat4 projectionMatrix)
{
}

glm::vec4 Camera::getPosition() const
{
	return m_worldTransform[3];
}
