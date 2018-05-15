#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
class Camera
{

public:

	void setPosition(glm::vec4 position);
	glm::vec4 getPosition() const;
	
	void translate(glm::vec4 positonmodifier); 

	const glm::mat4& getTransform()const { return m_worldTransform; }
	glm::mat4& getTransform() { return m_worldTransform; }

	glm::mat4 getViewMatric() const { return glm::inverse(m_worldTransform); }

	const glm::mat4& getProjectionMatrix() const; 
	void SetProjectionMatric(glm::mat4 projectionMatrix);

	glm::mat4 m_worldTransform = glm::mat4(1);
private:
	glm::mat4 ProjectionMatrix = glm::mat4(1);
	bool m_HasSetProjectionMatrix = false; 
};