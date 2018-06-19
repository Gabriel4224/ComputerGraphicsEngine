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
#include "NewOrbitCamera.h"
#include "FlyCamera.h"
class DemoApp : public MyApplication
{
public:
	virtual bool OnStartUp() override
	{
		glClearColor(0.55f, 0.35f, 0.0f, 1);

		aie::Gizmos::create(10000, 10000, 10000, 10000);
		m_OrbitingCam = new NewOrbitCamera({ 10,10,10 }, { 0,0,0 }, 0.2f);

		//Sets Up Camera 
		m_OrbitingCam->SetProjection(1, 16 / 9.0f, 1, 100.0f);
		//**********************************************************************************************
		// Loads in Shaders via file path
		//**********************************************************************************************
		m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/test.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/test.frag");

		m_PhongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/Phong.vert");
		m_PhongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/Phong.frag");

		m_TextureShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleTextured.vert");
		m_TextureShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleTextured.frag");

		m_TextureLightingShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/NormalMap.vert");
		m_TextureLightingShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/NormalMap.frag");
		
		//Diffuse lighting Adjustments 
		 m_Light.Diffuse = { 10, 1, 0 };
		 m_Light1.Diffuse = { 0, 0, 10 };
		 m_Light2.Diffuse = { 0, 10, 0 };
		 m_Light3.Diffuse = { 10, 0, 0 };
		 m_Light4.Diffuse = { 50, 0, 0 };
		 m_Light5.Diffuse = {0 , 50, 0 };

		//Specular lighting Adjustments 
		 m_Light.Specular = { 1, 1, 1 };
		 m_Light1.Specular = { 1, 1, 1 };
		 m_Light2.Specular = { 1, 1, 1 };
		 m_Light3.Specular = { 1, 1, 1 };
		 m_Light4.Specular = { 12, 12, 12 };
		 m_Light5.Specular = { 10, 10, 10 };


		 m_AmbientLight = { 1, 1, 1 };
		//**********************************************************************************************
		//Checks Errors in linking the shaders
		//**********************************************************************************************
		if (m_shader.link() == false)
		{
			printf("shader Error: %s\n ", m_shader.getLastError());
			return false;
		}
		if (m_PhongShader.link() == false)
		{
			printf("PhongShader Error: %s\n ", m_PhongShader.getLastError());
			return false;
		}
		//**********************************************************************************************
		//Loads In obj models via filepath 
		//**********************************************************************************************
		 if (m_SoulSpearMesh.load("./soulspear/soulspear.obj") == false)
		 {
		 	printf("Dragon Mesh Error!\n");
		 	return false;
		 }
		 if (m_CokeMesh.load("./CanMesh/mpm_vol.09_p35.obj") == false)
		 {
		 	printf("Dragon Mesh Error!\n");
		 	return false;
		 }
	      if (m_BunnyMesh.load("./stanford/Bunny.obj") == false)
	      {
	      	printf("Bunny Mesh Error!\n");
	      	return false;
	      }
		  if (m_DragonMesh.load("./stanford/Dragon.obj") == false)
		  {
			  printf("Dragon Mesh Error!\n");
			  return false;
		  }
		  if (m_TableMesh.load("./Table/diningtable.obj ") == false)
		  {
			  printf("Table Mesh Error!\n");
		 	  return false;
		  }
	    
		  if (m_TextureShader.link() == false)
		  {
		  	printf("TextureShader Error: %s\n ", m_TextureShader.getLastError());
		  	return false;    
		  }
		  if (m_TextureLightingShader.link() == false)
		  {
			  printf("TextureLightingShader Error: %s\n ", m_TextureShader.getLastError());
			  return false;
		  }
	     
	     //if (m_GridTexture.load("./textures/table.png") == false)
	     //{
	     //	printf("Failed to load Texture! \n");
	     //	return false;
	     //}
	
		m_quadMesh.initialiseQuad();
		//**********************************************************************************************
		// Size and position of ModelTransforms 
		//											
		//	{* * * * // Size of obj X 												
		//	 * * * * // Size of obj Y										
		//	 * * * * // Size of obj Z 								
		//	 * * * *}// Position of obj X ,Y ,Z , 
		//**********************************************************************************************
		 m_quadTransform = {
		 	20,0,0,0,
		 	0,20,0,0,
		 	0,0,20,0,
		 	0,0,0,1 };

		m_SoulSpearTransform = {
			1, 0, 0, 0,
			0, 1 ,0 , 0,
			0, 0, 1, 0,
			-8, 0, 0, 1.f
		};
		 m_CokeTransform = {
		 	0.025f, 0, 0, 0,
		 	0, 0.025f ,0 , 0,
		 	0, 0, 0.025f, 0,
		 	6, 0, 0, 1.f
		 };
		  m_BunnyTransform = {
		   	0.5f, 0, 0, 0,
		   	0, 0.5 ,0 , 0,
		   	0, 0, 0.5f, 0,
		   	0, 0, -7, 01.f
		   };
		  m_DragonTransform = {
		    0.5f, 0, 0, 0,
		    0, 0.5 ,0 , 0,
		    0, 0, 0.5f, 0,
		    0, 0, 6, 01.f
		  };
		  m_TableTransform =
		  {
		    0.15, 0, 0, 0,
		    0, 0.05 ,0 , 0,
		    0, 0, 0.15, 0,
		    -7, -6, 2, 1.f
		  };
		 glEnable(GL_DEPTH_TEST);
		 glDisable(GL_CULL_FACE);
		return true;
	}


	virtual void onShutDown() override
	{
		aie::Gizmos::destroy();
		//	delete m_Camera;
	}
	virtual void update() override
	{

		m_OrbitingCam->Update(0.0166f);

		if (glfwWindowShouldClose(getWindow()))
		{
			setRunning(false);
		}
		auto cameratransform = m_OrbitingCam->GetWorldTransform();

		//Rotates Lighting 
		float time = glfwGetTime();
	 	m_Light.Direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));
		m_Light1.Direction = glm::normalize(glm::vec3(0, glm::cos(time * 4), glm::sin(time * 4)));
		
		m_Light2.Direction = glm::normalize(glm::vec3(0, glm::cos(time * 2), glm::sin(time * 2)));
		m_Light3.Direction = glm::normalize(glm::vec3(0, glm::cos(time * 4), glm::sin(time * 4)));

		m_Light4.Direction = glm::normalize(glm::vec3(0, glm::cos(time * 2), glm::sin(time * 2)));
		m_Light5.Direction = glm::normalize(glm::vec3(0, glm::cos(time * 4), glm::sin(time * 4)));

		//**********************************************************************************************
		// Draws the Grid in the engine
		//**********************************************************************************************
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

	virtual void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Points camera at object
		glm::mat4 OrbitView = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
		// The field of view for the camera 
		glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, (float)GetWindowWidth() / (float)GetWidnowHeight(), 0.1f, 1000.0f);
		aie::Gizmos::draw(m_OrbitingCam->GetProjectionViewTransform());
		//**********************************************************************************************
		// Shader Bindings
		//**********************************************************************************************
	
		//Grabs Texture bind
		m_TextureShader.bind();
	    //SpearViewModel is focused on the SoulSpear.obj in scene
		auto SpearViewModel = m_OrbitingCam->GetProjectionViewTransform() * m_SoulSpearTransform;
		//Binds the Textures to SoulSpear.obj
		m_TextureShader.bindUniform("ProjectionViewModel", SpearViewModel);
		//Draws The SoulSpear
		m_SoulSpearMesh.draw();
		
		//CokeBottleViewModel is focused on the CokeBottle.obj and cokeCan (Both in the same obj) 
		
		//TableViewModel is focused on the diningtable.obj
		auto TableViewModel = m_OrbitingCam->GetProjectionViewTransform() * m_TableTransform;
		//Binds the Texture to the diningtable.obj
		m_TextureShader.bindUniform("ProjectionViewModel", TableViewModel);
		m_TableMesh.draw();

		m_PhongShader.bindUniform("SpecularPower", 1);

	    m_PhongShader.bind();
		//Binds AmbeintLighting 
		m_PhongShader.bindUniform("Ia", m_AmbientLight);

		//Binds Diffuse light Colour 
		m_PhongShader.bindUniform("Id", m_Light.Diffuse);
		m_PhongShader.bindUniform("Id1", m_Light1.Diffuse);
		//Binds Specular light to ambeintLighting 
		m_PhongShader.bindUniform("Ia", m_Light.Specular);
		m_PhongShader.bindUniform("Ia", m_Light1.Specular);
		//Binds the m_Light.Direction to LightDirection
	    m_PhongShader.bindUniform("LightDirection", m_Light.Direction);
		m_PhongShader.bindUniform("LightDirection1", m_Light1.Direction);
		
		auto CokeBottleViewModel = m_OrbitingCam->GetProjectionViewTransform() * m_CokeTransform;
		//Binds the Texture to the CokeBottle.obj
		m_TextureLightingShader.bindUniform("ProjectionViewModel", CokeBottleViewModel);
		m_PhongShader.bindUniform("ProjectionViewModel", CokeBottleViewModel);
		m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_CokeTransform)));
		m_CokeMesh.draw();
	
	
		m_PhongShader.bindUniform("Id", m_Light2.Diffuse);
		m_PhongShader.bindUniform("Id1", m_Light3.Diffuse);
		//Binds Specular light to ambeintLighting 
		m_PhongShader.bindUniform("Ia", m_Light2.Specular);
		m_PhongShader.bindUniform("Ia", m_Light3.Specular);
		//Binds the m_Light.Direction to LightDirection
		m_PhongShader.bindUniform("LightDirection", m_Light2.Direction);
		m_PhongShader.bindUniform("LightDirection1", m_Light3.Direction);


	    auto BunnyViewModel = m_OrbitingCam->GetProjectionViewTransform() * m_BunnyTransform;
		m_PhongShader.bindUniform("cameraPosition", glm::vec3( m_OrbitingCam->GetPosition()));
		
		//Binds the phong shader to the Bunnyviewmodel
	    m_PhongShader.bindUniform("ProjectionViewModel", BunnyViewModel);
	    m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_BunnyTransform)));
	    m_BunnyMesh.draw();

		m_PhongShader.bindUniform("Id", m_Light4.Diffuse);
		m_PhongShader.bindUniform("Id1", m_Light5.Diffuse);
		//Binds Specular light to ambeintLighting 
		m_PhongShader.bindUniform("Ia", m_Light4.Specular);
		m_PhongShader.bindUniform("Ia", m_Light5.Specular);
		//Binds the m_Light.Direction to LightDirection
		m_PhongShader.bindUniform("LightDirection", m_Light4.Direction);
		m_PhongShader.bindUniform("LightDirection1", m_Light5.Direction);

		auto DragonViewModel = m_OrbitingCam->GetProjectionViewTransform() * m_DragonTransform;
		m_PhongShader.bindUniform("cameraPosition", glm::vec3(m_OrbitingCam->GetPosition()));
		m_PhongShader.bindUniform("ProjectionViewModel", DragonViewModel);
		m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_DragonTransform)));
		m_DragonMesh.draw();
	}
private:

	NewOrbitCamera * m_OrbitingCam;
	FlyCamera * m_FlyCam;
};


int main(){

	auto theApp = new DemoApp();
	theApp->setRunning(true);
	//	theApp->gameloop();
	return theApp->run("Application", 720, 1280, false);
	delete theApp;

}