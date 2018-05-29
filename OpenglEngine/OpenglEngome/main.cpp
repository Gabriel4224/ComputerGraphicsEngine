#include "MyApplication.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>
#pragma warning (push)
#pragma warning (disable : 4201)
#pragma warning (disable : 4310)
#include "Gizmos.h"
#include "Camera.h"
class DemoApp : public MyApplication
{

public:
	virtual bool OnStartUp() override
	{
		aie::Gizmos::create(10000, 10000, 10000, 10000);
		m_Camera = new Camera();


		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleVert.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleFrag.frag");
		if (m_BunnyMesh.load("./stanford/bunny.obj") == false)
		{
			printf("Bunny Mesh Error!\n");
			return false;
		}

		//m_PhongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/PhongVert.vert");
		//m_PhongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/PhongFrag.frag");

		if (m_shader.link() == false)
		{
			printf("shader Error: %s\n ", m_shader.getLastError());
			return false;
		}
	//if (m_PhongShader.link() == false)
	//{
	//	printf("shader Error: %s\n ", m_PhongShader.getLastError());
	//	return false;
	//}
      // Mesh::Vertex vertices[4];
      // vertices[0].position = { -0.5f,0,0.5f,1 };
      // vertices[1].position = { 0.5f,0,0.5f,1 };
      // vertices[2].position = { -0.5f,0,-0.5f,1 };
      // vertices[3].position = { 0.5f,0,-0.5f,1 };
      // 
      // unsigned int Indices[6] = { 0,1,2,2,1,3 };
      // m_quadMesh.initialise(4, vertices, 6, Indices);
       
		m_quadMesh.initialiseQuad();

		m_Light.Diffuse = { 1,1,1 };
		m_Light.Specular = { 1,0,1 };
		m_AmbientLight = { 0.25f,0.25f,0.25f };

		m_Camera->setPosition({ 0,5,30,1 });
		 m_quadTransform = {
		 	10,0,0,0,
		 	0,10,0,0,
		 	0,0,10,0,
		 	0,0,0,1 };
	//	m_BunnyTransform = {
	//		0.5f,0,0,0,
	//		0,0.5f,0,0,
	//		0,0,0.5f,0,
	//		0,0,0,1
	//	};
		return true;
 	}
	virtual void render() override
	{
		glm::mat4 view = m_Camera->getViewMatric(); 
		glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,(float)GetWindowWidth() / (float)GetWidnowHeight(), 0.1f, 1000.0f);

		m_shader.bind(); 
		//glm::mat4 view = glm::lookAt(glm::vec3(20, 20, 20), glm::vec3(0), glm::vec3(0, 1, 0));
		 
		auto pvm = projection * view * m_quadTransform;
		m_shader.bindUniform("ProjectionViewModel",pvm );
	//m_BunnyMesh.draw();
      //  
      //  m_PhongShader.bind();
      // 
      //  m_PhongShader.bindUniform("Ia", m_AmbientLight);
      //  m_PhongShader.bindUniform("Id", m_Light.Diffuse);
      //  m_PhongShader.bindUniform("Is", m_Light.Specular);
      //  m_PhongShader.bindUniform("LightDirection", m_Light.Direction);
      //  
      //  auto pvmPhong = projection * view * m_ModelTransform;
      //  m_PhongShader.bindUniform("PhongProjectionViewModel", pvmPhong);
      //
      // m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_ModelTransform)));
		
		m_quadMesh.draw(); 
		//Mesh::Vertex vertices[6];
		//
		//vertices[0].position = { -0.5f,0,0.5f,1 };
		//vertices[1].position = { 0.5f,0,0.5f,1 };
		//vertices[2].position = { -0.5f,0,-0.5f,1 };
		//
		//vertices[3].position = { -0.5f,0,-0.5f,1 };
		//vertices[4].position = { 0.5f,0,0.5f,1 };
		//vertices[5].position = { 0.5f,0,-0.5f,1 };
		//m_quadMesh.initialise(6, vertices);


		//m_quadMesh.draw();

		aie::Gizmos::draw(projection * view );
	}
	virtual void onShutDown() override
	{
		aie::Gizmos::destroy();
		delete m_Camera;
	}
	virtual void update() override
	{
	time_t start = time(0);

	m_Light.Direction = glm::normalize(glm::vec3(glm::cos(start * 2), glm::sin(start * 2), 0)); 

	if (glfwWindowShouldClose(getWindow()))
	{
		setRunning(false); 
	}
	auto& cameratransform = m_Camera->getTransform(); 

	auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0,1,0 });
	m_Camera->translate(glm::vec4{ 0,0,1,0 } *getDeltaTime() * 5.0f);
	
	aie::Gizmos::addTransform(glm::mat4(1), 10);
	//aie::Gizmos::add2DAABB(glm::vec3{ 0,0,0 }, glm::vec3{ 5,5,5 }, glm::vec4{ 1,0,0,1 });

	}

private:
	Camera *m_Camera; 
};


int main()
{

	auto theApp = new DemoApp();
	theApp->setRunning(true);
//	theApp->gameloop();
	return theApp->run("Application", 1280, 720, false);
	delete theApp;

}