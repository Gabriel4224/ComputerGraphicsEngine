#pragma once
#include "Camera.h"
#include <glm/ext.hpp>

class OrbitingCamera : public Camera
{
public:
	OrbitingCamera() = default;
	OrbitingCamera(const glm::vec3& Position, const glm::vec3& TargetLocation, float RotationSpeed);

	void SetUpOrbit(const glm::vec3& Position, const glm::vec3& TargetLocation, float RotationSpeed);
	void Update(float DeltaTime);

protected:
	glm::vec3 m_TargetOffset;
	glm::vec3 m_LookAtTarget; 
	float m_RotationSpeed;

	~OrbitingCamera();
};

