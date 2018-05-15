#include "MyApplication.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Gizmos.h"



int MyApplication::run(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen)
{


	auto success = Initialize(WindowTile, WindowHeight, Windowwidth, Fullscreen);

	if (!success)
	{
		return -1;
	}
	
	if  (!OnStartUp())
	{
		ShutDown();
		return -2;
	}
	gameloop(); 
	onShutDown(); 
	ShutDown();
	return 0;
}

bool MyApplication::Initialize(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen)
{
	glfwInit();
	

	if (glfwInit() == false)
		return -1;

	GLFWmonitor* monitor = nullptr; 
	if (Fullscreen)
	{
		monitor = glfwGetPrimaryMonitor(); 
	}
	GLFWwindow* window = glfwCreateWindow(WindowHeight, Windowwidth,WindowTile.c_str(), monitor, nullptr);


	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{

		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	m_window = window;
	m_WidnowHeigh = WindowHeight;
	m_WindowWidth = Windowwidth;
	m_isFullScreen = Fullscreen;	
	m_PreviousTime = std::chrono::high_resolution_clock::now();
	m_applicationStartTime = m_PreviousTime; 
	return true; 
}


void MyApplication::ShutDown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void MyApplication::gameloop()
{
	while (m_isRunning)
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto timetaken = now - m_PreviousTime; 

		//auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timetaken);
//		m_dt = std::chrono::duration<float>(timetaken).count;
		m_PreviousTime = now;

		auto elapsedTime = now - m_applicationStartTime;
	//	m_elapsedTime = std::chrono::duration<float>(elapsedTime).count;
		
		update();
		render(); 
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	//while (glfwWindowShouldClose(m_window) == false &&
	//	glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	glClearColor(0, 0.50f, 0.60f, 1);
	//	glEnable(GL_DEPTH);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//
	//	aie::Gizmos::clear();
	//
	//	aie::Gizmos::addTransform(glm::mat4(1));
	//
	//	glm::vec4 white(1);
	//	glm::vec4 black(0, 0, 0, 1);
	//
	//	for (int i = 0; i < 21; i++)
	//	{
	//		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
	//			glm::vec3(-10 + i, 0, -10),
	//			i == 10 ? white : black);
	//		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
	//			glm::vec3(-10, 0, -10 + i),
	//			i == 10 ? white : black);
	//	}
	//	//aie::Gizmos::draw(projection * view);

	
}




