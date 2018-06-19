#pragma once
#include <iostream>
#include <chrono>
#include "Shader.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Mesh.h"
#include "OBJMesh.h"
#include "FlyCamera.h"

class MyApplication
{
public:

	virtual bool OnStartUp() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onShutDown() = 0;

	int run(std::string WindowTile, int WindowHeight, int Windowwidth, bool Fullscreen);

    bool Initialize(std::string WindowTile, int WindowHeight, int Windowwidth,bool Fullscreen);
    void gameloop();
    void ShutDown();

	void setRunning(bool running)  { m_isRunning = running;  }

protected:
	// Windows Properties 
	struct GLFWwindow * getWindow() const { return m_window; }
	int GetWidnowHeight() const { return m_WidnowHeigh; }
	int GetWindowWidth() const {return m_WindowWidth;}
	bool GetFullscreen() const { return m_isFullScreen; }
	bool getRunning() const { return m_isRunning; }
	
	// Gets App run time 
	float getEsalpsedtime() const { return m_elapsedTime; }
	float getDeltaTime() const { return DeltaTime; }
	// What the camera can see 
	glm::mat4 m_viewMatrix; 
	// FOV of camera 
	glm::mat4 m_projectileMatrix; 

	// Shaders 
	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_PhongShader;
	aie::ShaderProgram	m_TextureShader;
	aie::ShaderProgram	m_TextureLightingShader;

	// Textures
	aie::Texture m_GridTexture; 
	aie::Texture m_Apple; 

	//OBJ Meshes / regular Meshes 
	aie::OBJMesh		m_CokeMesh; 
	aie::OBJMesh		m_SoulSpearMesh;
	aie::OBJMesh		m_BunnyMesh;
	aie::OBJMesh		m_DragonMesh;
	aie::OBJMesh		m_TableMesh; 
	Mesh				m_quadMesh;

	//Mat4 Transforms 
	glm::mat4			m_quadTransform;
	glm::mat4			m_DragonTransform;
	glm::mat4			m_CokeTransform;
	glm::mat4			m_SoulSpearTransform;
	glm::mat4			m_BunnyTransform; 
	glm::mat4			m_TableTransform; 

	struct Light 
	{
		glm::vec3 Direction; 

	 	glm::vec3 Diffuse; 
	 	glm::vec3 Specular;
	};
	
	Light				m_Light; 
	Light				m_Light1;
	Light				m_Light2;
	Light				m_Light3;
	Light				m_Light4;
	Light				m_Light5;
 	glm::vec3			m_AmbientLight; 
	GLFWwindow * m_window = nullptr;
private:
	bool m_isFullScreen;
	bool m_isRunning; 
	int m_WindowWidth = 1280;
	int m_WidnowHeigh = 720;
	float DeltaTime = 0.00f;
	float m_elapsedTime = 0.0f; 
	std::chrono::high_resolution_clock::time_point m_PreviousTime; 
	std::chrono::high_resolution_clock::time_point m_applicationStartTime;
};

