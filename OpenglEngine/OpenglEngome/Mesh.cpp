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

	Vertex verticles[6];
	verticles[0].position = { -0.5f,0,0.5f,1 };
	verticles[1].position = { 0.5f,0,0.5f,1 };
	verticles[2].position = { -0.5f,0,-0.5f,1 };
	verticles[3].position = { -0.5f,0,-0.5,1 };
	verticles[4].position = { 0.5f,0,0.5f,1 };
	verticles[5].position = { 0.5f,0,-0.5f,1 };
	
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verticles, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	tricount = 2;
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
	
	aie::ShaderProgram shader;
	//TODO: add shader file path 
	shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

	if (shader.link() == false)
	{
		printf("Shader Error: %s \n ", shader.getLastError()); 
	}

	
	

}
