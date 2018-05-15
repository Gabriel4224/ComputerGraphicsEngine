#include "MyApplication.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Gizmos.h"

#include "Camera.h"
class DemoApp : public MyApplication
{

public :
	virtual bool OnStartUp() override
	{
		aie::Gizmos::create(1000, 1000, 1000, 1000);
		m_Camera = new Camera(); 


		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

		if (m_shader.link() == false)
		{
			printf("shader Error: %s\n ", m_shader.getLastError());
			return false;
		}
		m_quadMesh.initialiseQuad();
		m_Camera->setPosition({ 0,0,20,1 });
		m_quadTransform = {
			10,0,0,0,
			0,10,0,0,
			0,0,10,0,
			0,0,0,1 };
		return true;
	}
	virtual void render() override
	{
		glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,(float)GetWindowWidth() / (float)GetWidnowHeight(), 0.1f, 1000.0f);

		m_shader.bind(); 
		//glm::mat4 view = glm::lookAt(glm::vec3(20, 20, 20), glm::vec3(0), glm::vec3(0, 1, 0));
		glm::mat4 view = m_Camera->getViewMatric(); 
		 
		auto pvm = projection * view * m_quadTransform;
		m_shader.bindUniform("ProjectionViewModel",pvm );
		
		m_quadMesh.draw(); 

		aie::Gizmos::draw(projection * view );
	}
	virtual void onShutDown() override
	{
		aie::Gizmos::destroy();
		delete m_Camera;
	}
	virtual void update() override
	{
		if (glfwWindowShouldClose(getWindow()))
		{
			setRunning(false); 
		}
		auto& cameratransform = m_Camera->getTransform(); 

		auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0,1,0 });
		m_Camera->translate(glm::vec4{ 0,0,1,0 } *getDeltaTime() * 5.0f);
		
		aie::Gizmos::addTransform(glm::mat4(1), 10);
		aie::Gizmos::add2DAABB(glm::vec3{ 0,0,0 }, glm::vec3{ 5,5,5 }, glm::vec4{ 1,0,0,1 });

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