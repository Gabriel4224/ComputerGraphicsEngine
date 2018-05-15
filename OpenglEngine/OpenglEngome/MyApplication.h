#pragma once
#include <iostream>
#include <chrono>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Mesh.h"
class MyApplication
{
public:

	virtual bool OnStartUp() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onShutDown() = 0;

	int run(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen);
	//{
	//return	 0;
	//}
	 bool Initialize(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen);
	 void gameloop();
	 void ShutDown();
	//virtual void update(float deltaTime); 

	void setRunning(bool running)  { m_isRunning = running;  }


protected:
	struct GLFWwindow * getWindow() const { return m_window; }
	int GetWidnowHeight() const { return m_WidnowHeigh; }
	int GetWindowWidth() const {return m_WindowWidth;}
	bool GetFullscreen() const { return m_isFullScreen; }

	bool getRunning() const { return m_isRunning; }
	
	float getEsalpsedtime() const { return m_elapsedTime; }
	float getDeltaTime() const { return m_dt; }

	glm::mat4 m_viewMatrix; 
	glm::mat4 m_projectileMatrix; 

	aie::ShaderProgram	m_shader;
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;
	
private:
	GLFWwindow * m_window = nullptr;
	bool m_isFullScreen;
	bool m_isRunning; 
	int m_WindowWidth = 720;
	int m_WidnowHeigh = 1280;
	float m_dt = 0.00f;
	float m_elapsedTime = 0.0f; 
	std::chrono::high_resolution_clock::time_point m_PreviousTime; 
	std::chrono::high_resolution_clock::time_point m_applicationStartTime;
};

