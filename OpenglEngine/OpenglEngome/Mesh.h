#pragma once
#include <gl_core_4_4.h>

#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "OBJMesh.h"

class Mesh
{
public:
	Mesh() : tricount(0), vao(0),vbo(0),ibo(0) {}

	~Mesh();
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};
	void initialiseQuad();

	virtual void draw(); 
protected:
	unsigned int tricount;
	// vao = Vertex Array Object 
	// vbo = Vertex Buffer Object
	// ibo = Index Buffer Object
	unsigned int vao, vbo, ibo; 
};

