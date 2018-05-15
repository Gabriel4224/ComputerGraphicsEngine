#include "FirstPersonCamera.h"



void FirstPersonCamera::update(GLFWWindow * window, float deltaTime)
{
	if (window == nullptr) return
		assert(window != nullptr);

	auto& forward = getTransform()[2];
	auto& right = getTransform()[0];
	auto& up = getTransform()[1];
	
	auto worldUp = glm::vec4{ 0,1,0,0 };

//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//	{
//		translate(forward * deltaTime * -getmoveSpeed();
//	}
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//	{
//		translate(forward * deltaTime * getmoveSpeed();
//	}
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//	{
//		translate(right * deltaTime * -getmoveSpeed();
//	}
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//	{
//		translate(right * deltaTime * getmoveSpeed();
//	}
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
//	{
//		translate(forward * deltaTime * -getmoveSpeed();
//	}
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
//	{
//		auto rot = glm::angleAxis(m_rotationSpeed, glm::vec3(up));
//	}

}

FirstPersonCamera::FirstPersonCamera()
{
}


FirstPersonCamera::~FirstPersonCamera()
{
}
