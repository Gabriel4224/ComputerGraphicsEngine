#pragma once
#include <gl_core_4_4.h>

#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

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
	void initialise(unsigned int vertexCount, const Vertex* verticles, unsigned int indexCount = 0, unsigned int* indices = nullptr);

	virtual void draw(); 
protected:
	unsigned int tricount;
	unsigned int vao, vbo, ibo; 
};

