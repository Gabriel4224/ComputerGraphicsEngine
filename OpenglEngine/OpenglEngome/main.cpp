
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <iostream>
int main()
{
	if (glfwInit() == false)
		return -1; 
	


	GLFWwindow* window = glfwCreateWindow(1280, 720, "My first REEEEEEEEEEEEEEEEE: ", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2; 
	}
	
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{

		glfwDestroyWindow(window);
		glfwTerminate();
		return -3; 
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << "GL: " << major << " " << minor << "\n"; 
	
	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClearColor(0, 0.50f, 0.60f, 1);
		glEnable(GL_DEPTH);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window); 
	glfwTerminate(); 
}