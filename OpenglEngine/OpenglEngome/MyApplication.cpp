#include "MyApplication.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Gizmos.h"


int MyApplication::run(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen)
{
	auto success = Initialize(WindowTile, WindowHeight, Windowwidth, Fullscreen);
	// If the application doesent build successfully it shuts down 
	if (!success)
	{
		return -1;
	}
	// Application shutdown
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

bool MyApplication::Initialize(std::string WindowTile, int WindowHeight, int Windowwidth,  bool Fullscreen)
{
	glfwInit();


	if (glfwInit() == false)
		return -1;

	GLFWmonitor* monitor = nullptr; 
	if (Fullscreen)
	{
		monitor = glfwGetPrimaryMonitor(); 
	}
	GLFWwindow* window = glfwCreateWindow(Windowwidth, WindowHeight,WindowTile.c_str(), monitor, nullptr);


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
	//Goes through The application every frame 
	while (m_isRunning)
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto timetaken = now - m_PreviousTime; 

		m_PreviousTime = now;

		auto elapsedTime = now - m_applicationStartTime;
		
		update();
		render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	
}




