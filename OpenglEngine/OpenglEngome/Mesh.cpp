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
	// Checks that the mesh inst initialized twice 
	assert(vao == 0);
	//Generates buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//binds vertex arrays 
	glBindVertexArray(vao);
	//binds vertex buffer 
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
	verticles[0].texCoord = { 0, 1 };	//Bottom Left
	verticles[1].texCoord = { 1, 1 };	//Bottom Right
	verticles[2].texCoord = { 0, 0 };	//Top Left
	verticles[3].texCoord = { 0, 0 };	//Top Left
	verticles[4].texCoord = { 1, 1 };	//Bottom Right
	verticles[5].texCoord = { 1, 0 };	//Top Right

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	//Vertex Normals
	verticles[0].normal = {0,1,0,0};
	verticles[1].normal = {0,1,0,0};
	verticles[2].normal = {0,1,0,0};
	verticles[3].normal = {0,1,0,0};
	verticles[4].normal = {0,1,0,0};
	verticles[5].normal = {0,1,0,0};
	
	//Fills vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), verticles, GL_STATIC_DRAW);

	//Enables first element as position 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	tricount = 2;
}

void Mesh::draw()
{
	//Draws Tri's on the object 
	glBindVertexArray(vao);
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * tricount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * tricount);
	}
	

}
