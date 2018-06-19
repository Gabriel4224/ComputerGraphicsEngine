#pragma once
#include "Camera.h"
#include <GLFW\glfw3.h>

class FlyCamera : public Camera 
{
public:
	
	FlyCamera(struct GLFWwindow* window, float MoveSpeed,float RotationSpeed);
	~FlyCamera();

	void Update(float DeltaTime) override;
	// Sets a window so the scene can track the mouse cursor  
	void setGLFWwindow(class GLFWwindow* window)
	{
		m_Window = window; 
	}

	struct GLFWwindow * m_Window; 
private:
	// Camera MovementSpeed 
	float m_MovementSpeed = 20.0f;
	// Camera RotationSpeed 
	float m_RotationSpeed = 10.0f;

};

