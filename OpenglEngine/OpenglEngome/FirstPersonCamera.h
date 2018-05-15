#pragma once
#include "Camera.h"
class FirstPersonCamera : public Camera
{
public:
	void update(struct GLFWWindow* window, float deltaTime); //override
	
	FirstPersonCamera();
	~FirstPersonCamera();

	float getmoveSpeed() { return m_moveSpeed; }
	void setMoveSpeed(float val) { m_moveSpeed = val; }
	float m_moveSpeed = 0.0f;
};

