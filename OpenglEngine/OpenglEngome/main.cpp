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
#include "OrbitingCamera.h"
class DemoApp : public MyApplication
{
public:
	virtual bool OnStartUp() override
	{
		glClearColor(0.65, 0.65f, 0.65f, 1);


		aie::Gizmos::create(10000, 10000, 10000, 10000);
		//m_Camera = new Camera();
		m_OrbitingCam = new OrbitingCamera();
		//m_OrbitingCam->GetDirection();
		m_OrbitingCam->SetlookAt(glm::vec3(5), glm::vec3(0));

		//m_OrbitingCam->setPosition({ 1,4,20,1 });
		m_OrbitingCam->SetPerspective( 1 ,16 / 9.0f,1,100.0f );
		//m_OrbitingCam->SetlookAt(m_OrbitingCam->GetPosition(), m_OrbitingCam->GetDirection(), m_OrbitingCam->GetUpVector());
		//m_OrbitingCam->SetlookAt(glm::vec3(5, 10, 20), glm::vec3(0, 2, 0), glm::vec3(0, 5, 1));

		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleVert.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleFrag.frag");
		//m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleTextured.vert");
		//m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleTextured.frag");
		if (m_shader.link() == false)
		 {
		 	printf("shader Error: %s\n ", m_shader.getLastError());
		 	return false;
		 }

		if (m_DragonMesh.load("./stanford/Dragon.obj") == false)
		 {
		 	printf("Dragon Mesh Error!\n");
		 	return false;
		 }

		if (m_DragonTexture.load("./shaders/numbered_grid.tga") == false)
		{
			printf("Failed to load Texture! \n");
			return false;
		 }
		// m_PhongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/PhongVert.vert");
		// m_PhongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/PhongFrag.frag");
		
		//if (m_PhongShader.link() == false)
		// {
		// 	printf("shader Error: %s\n ", m_PhongShader.getLastError());
		// 	return false;
		// }
		m_quadMesh.initialiseQuad();

		m_Light.Diffuse = { 1,1,1 };
		m_Light.Specular = { 1,0,1 };
		m_AmbientLight = { 0.25f,0.25f,0.25f };

		//m_Camera->setPosition({ 0,5,30,1 });

	 	// m_quadTransform = {
	 	// 	10,0,0,0,
	 	// 	0,10,0,0,
	 	// 	0,0,10,0,
	 	// 	0,0,0,1 };

		m_DragonTransform = {
			0.3, 0, 0, 0,
			 0, 0.3 ,0 , 0,
			 0, 0, 0.3, 0,
			 0, 0, 0, 1.f
	     };

		return true;
 	}

	virtual void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    //glm::mat4 view = m_Camera->getViewMatric(); 
		//glm::mat4 OrbitView = m_OrbitingCam->GetViewTransform();
		//glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,(float)GetWindowWidth() / (float)GetWidnowHeight(), 0.1f, 1000.0f);

	// m_PhongShader.bind();
	// m_PhongShader.bindUniform("LightDirection", m_Light.Direction);
	// m_PhongShader.bindUniform("Ia", m_AmbientLight);
	// m_PhongShader.bindUniform("Id", m_Light.Diffuse);
	// m_PhongShader.bindUniform("Is", m_Light.Specular);

		//glm::mat4 view = glm::lookAt(glm::vec3(20, 20, 20), glm::vec3(0), glm::vec3(0, 1, 0));
	
	//m_PhongShader.bindUniform("ProjectionViewModel", pvm);
	//
	//m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_DragonTransform)));

	//m_quadMesh.draw(); 

	glm::mat4 OrbitView = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, (float)GetWindowWidth() / (float)GetWidnowHeight(), 0.1f, 1000.0f);
	aie::Gizmos::draw(m_OrbitingCam->GetProjectionViewTransform());

//	m_OrbitingCam->SetUpOrbit(m_OrbitingCam->GetPosition(), , 0.5f);
	//m_OrbitingCam->SetUpOrbit(glm::vec3(0), (glm::vec3(5), glm::vec3(0)),0.8f);

	auto pvm = m_OrbitingCam->GetProjectionViewTransform() * m_DragonTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
//	m_shader.bindUniform("DiffuseTexture", 0);
	m_shader.bind();

	m_DragonMesh.draw();

	}

	virtual void onShutDown() override
	{
		aie::Gizmos::destroy();
	//	delete m_Camera;
	}
	virtual void update() override
	{
	time_t start = time(0);
	m_Light.Direction = glm::normalize(glm::vec3(glm::cos(start * 2), glm::sin(start * 2), 0)); 

	if (glfwWindowShouldClose(getWindow()))
	{
		setRunning(false); 
	}
//	auto& cameratransform = m_Camera->getTransform(); 
	auto cameratransform = m_OrbitingCam->GetWorldTransform();
	float DeltaTime = 1; 
	m_OrbitingCam->Update(DeltaTime);
	auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0,1,0 });
    //m_Camera->translate(glm::vec4{ 0,0,1,0 } *getDeltaTime() * 5.0f);
	//m_OrbitingCam->translate(glm::vec4{ 0,0,1,0 } *getDeltaTime() * 5.0f);

	aie::Gizmos::addTransform(glm::mat4(1), 1);
	 	glEnable(GL_DEPTH);
	 
	 	aie::Gizmos::clear();
	 
	 	aie::Gizmos::addTransform(glm::mat4(1));
	 
	 	glm::vec4 white(1);
	 	glm::vec4 black(0, 0, 0, 1);
	 
	 	for (int i = 0; i < 21; i++)
	 	{
	 		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
	 			glm::vec3(-10 + i, 0, -10),
	 			i == 10 ? white : black);
	 		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
	 			glm::vec3(-10, 0, -10 + i),
	 			i == 10 ? white : black);
	 	}
	aie::Gizmos::add2DAABB(glm::vec3{ 0,0,0 }, glm::vec3{ 5,5,5 }, glm::vec4{ 1,0,0,1 });

	}

private:
//	Camera *m_Camera; 
	OrbitingCamera *m_OrbitingCam;
};


int main()
{

	auto theApp = new DemoApp();
	theApp->setRunning(true);
//	theApp->gameloop();
	return theApp->run("Application", 720, 1280, false);
	delete theApp;

}