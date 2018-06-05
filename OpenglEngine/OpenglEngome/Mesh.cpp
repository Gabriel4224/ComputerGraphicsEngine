#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Shader.h"
#include "Mesh.h"


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &vbo);
	glDeleteVertexArrays(1, &ibo);
}

void Mesh::initialiseQuad()
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//Vertex Positions
	Vertex verticles[6];
	verticles[0].position = { -0.5f,0,0.5f,1 };
	verticles[1].position = { 0.5f,0,0.5f,1 };
	verticles[2].position = { -0.5f,0,-0.5f,1 };
	verticles[3].position = { -0.5f,0,-0.5,1 };
	verticles[4].position = { 0.5f,0,0.5f,1 };
	verticles[5].position = { 0.5f,0,-0.5f,1 };

    //Vertex TexCoord
	//Bottom Left
	verticles[0].texCoord = { 0, 1 };
	//Bottom Right
	verticles[1].texCoord = { 1, 1 };
	//Top Left
	verticles[2].texCoord = { 0, 0 };
	//Top Left
	verticles[3].texCoord = { 0, 0 };
	//Bottom Right
	verticles[4].texCoord = { 1, 1 };
	//Top Right
	verticles[5].texCoord = { 1, 0 };
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	//Vertex Normals
	verticles[0].normal = {0,1,0,0};
	verticles[1].normal = {0,1,0,0};
	verticles[2].normal = {0,1,0,0};
	verticles[3].normal = {0,1,0,0};
	verticles[4].normal = {0,1,0,0};
	verticles[5].normal = {0,1,0,0};
	
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verticles, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	tricount = 2;
}

void Mesh::initialise(unsigned int vertexCount, const Vertex * verticles, unsigned int indexCount, unsigned int * indices)
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER,  vertexCount * sizeof(Vertex), verticles, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		tricount = indexCount / 3; 
	}
	else
	{
		tricount = vertexCount / 3;
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * tricount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * tricount);
	}
	
	aie::ShaderProgram m_Shader;
	aie::ShaderProgram m_PhongShader;

	//TODO: add shader file path 
	// m_Shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleVert.vert");
	// m_Shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleFrag.frag");
	 m_Shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/SimpleVert.vert");
	 m_Shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/SimpleFrag.frag");
	//m_BunnyMesh.load("./stanford/bunny.obj");
	//
	 m_PhongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/PhongVert.vert");
	 m_PhongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/PhongFrag.frag");
	if (m_Shader.link() == false)
	{
		printf("Shader Error: %s \n ", m_Shader.getLastError());
	}

	
	

}
