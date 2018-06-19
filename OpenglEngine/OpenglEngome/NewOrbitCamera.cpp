#include "NewOrbitCamera.h"


NewOrbitCamera::NewOrbitCamera(glm::vec3 CameraLocation, glm::vec3 TargetLocation, float RotationSpeed, glm::vec3 RotationAxis)
{
	Setup(CameraLocation, TargetLocation, RotationSpeed, RotationAxis);
}

void NewOrbitCamera::Setup(glm::vec3 CameraLocation, glm::vec3 TargetLocation, float RotationSpeed, glm::vec3 RotationAxis)
{
	m_RotationAxis = RotationAxis;
	m_RotationSpeed = RotationSpeed;
	m_TargetLocation = TargetLocation;

	m_Offset = CameraLocation - TargetLocation;
	SetlookAt(CameraLocation, TargetLocation);

}

void NewOrbitCamera::Update(float DeltaTime)
{
	glm::quat Rotation = glm::angleAxis(m_RotationSpeed * DeltaTime, m_RotationAxis);

	glm::vec4 RotatedOffset = glm::mat4_cast(Rotation) * glm::vec4(m_Offset, 0);

	m_Offset = RotatedOffset;

	SetlookAt(m_TargetLocation + m_Offset, m_TargetLocation); 
}

