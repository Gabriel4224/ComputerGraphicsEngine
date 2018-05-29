#include "OrbitingCamera.h"

OrbitingCamera::OrbitingCamera(const glm::vec3 & Position, const glm::vec3 & TargetLocation, float RotationSpeed = 0.2f)
{
	SetUpOrbit(Position, TargetLocation, RotationSpeed);
}

void OrbitingCamera::SetUpOrbit(const glm::vec3 & Position, const glm::vec3 & TargetLocation, float RotationSpeed)
{
	m_LookAtTarget = TargetLocation;
	m_TargetOffset = Position - TargetLocation;
	m_RotationSpeed = RotationSpeed;
}

void OrbitingCamera::Update(float DeltaTime)
{
	auto Rotator = glm::angleAxis(m_RotationSpeed * DeltaTime, glm::vec3{ 0,1,0 });
	m_TargetOffset = glm::mat4_cast(Rotator) * glm::vec4{ m_TargetOffset,0 };
	glm::vec3 LookAt = (m_LookAtTarget + m_TargetOffset, m_LookAtTarget );
}

OrbitingCamera::~OrbitingCamera()
{
}