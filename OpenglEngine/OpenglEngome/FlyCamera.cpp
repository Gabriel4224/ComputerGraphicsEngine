#include "FlyCamera.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
FlyCamera::FlyCamera(GLFWwindow * window, float MoveSpeed, float RotationSpeed)
	:m_Window(window)
	,m_MovementSpeed(MoveSpeed)
	,m_RotationSpeed( RotationSpeed)
{

}

FlyCamera::~FlyCamera()
{
}

void FlyCamera::Update(float DeltaTime)
{
	glm::mat4 CameraTransform = GetWorldTransform(); 

	// Move the Camera With WASD 
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * -CameraTransform[2];
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * CameraTransform[2];
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * -CameraTransform[0];
	}	
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * CameraTransform[0];
	}
	//Move the camera up and down using TAB and SHIFT 
	if (glfwGetKey(m_Window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * glm::vec4{ 0,1,0,0 };
	}
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		CameraTransform[3] += m_MovementSpeed * DeltaTime * CameraTransform[1];
	}
	//Rotate Camera on Y axis with Q and E 
	if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		glm::quat Rotation = glm::angleAxis(-m_RotationSpeed * DeltaTime, glm::vec3(CameraTransform[1]));
	
		CameraTransform = glm::mat4_cast(Rotation) * CameraTransform;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
	{
		glm::quat Rotation = glm::angleAxis(-m_RotationSpeed * DeltaTime, glm::vec3(CameraTransform[1]));

		CameraTransform = glm::mat4_cast(Rotation) * CameraTransform;
	}
	//Rotate Camera on X axis with F and T 
	if (glfwGetKey(m_Window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glm::quat Rotation = glm::angleAxis(-m_RotationSpeed * DeltaTime, glm::vec3(CameraTransform[0]));

		CameraTransform = glm::mat4_cast(Rotation) * CameraTransform;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_T) == GLFW_PRESS)
	{
		glm::quat Rotation = glm::angleAxis(-m_RotationSpeed * DeltaTime, glm::vec3(CameraTransform[0]));

		CameraTransform = glm::mat4_cast(Rotation) * CameraTransform;
	}
}
