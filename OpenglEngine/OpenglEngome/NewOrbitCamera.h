#pragma once
#include "Camera.h"
#include <glm\ext.hpp>

class NewOrbitCamera: public Camera 
{
public:
	NewOrbitCamera(glm::vec3 CameraLocation, glm::vec3 TargetLocation, float RotationSpeed = glm::pi<float>(), glm::vec3 RotationAxis = glm::vec3(0, 1, 0));
	~NewOrbitCamera() {};
	void Setup(glm::vec3 CameraLocation, glm::vec3 TargetLocation, float RotationSpeed = glm::pi<float>(), glm::vec3 RotationAxis = glm::vec3(0, 1, 0));
	void Update(float DeltaTime) override; 
private:
	glm::vec3 m_TargetLocation; 
	glm::vec3 m_RotationAxis; 
	glm::vec3 m_Offset;
	float m_RotationSpeed; 
};

