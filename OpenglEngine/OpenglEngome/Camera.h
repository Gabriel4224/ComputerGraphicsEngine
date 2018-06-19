#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
class Camera
{

public:
	virtual ~Camera() {};
	//virtual void Update(double DeltaTime) overri;
	void SetProjection(const float FovY, const float AspectRatio, const float NearDistance, const float FarDistance);
	void SetlookAt(const glm::vec3 &CameraPos, const glm::vec3 & ToPosition, const glm::vec3 &YAxis = glm::vec3(0.0f, 1.0f, 0.0f));
	void setPosition(glm::vec4 position);

	virtual void Update(float DeltaTime); 
	glm::vec4 GetPosition() const;
	glm::vec3 GetDirection() const;
	glm::vec3 GetUpVector() const;
	glm::mat4 GetWorldTransform() const;
	glm::mat4 GetViewTransform() const;
	glm::mat4 GetProjectionTransform() const;
	glm::mat4 GetProjectionViewTransform() const;


	void translate(glm::vec4 positonmodifier); 

protected:
	Camera(); 
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix; 
	glm::mat4 m_ProjectionXViewMatrix; 
	void UpdateMatrices(); 
	
	
	
	glm::mat4 getViewMatric() const { return glm::inverse(m_worldTransform); }
	

	const glm::mat4& getTransform()const { return m_worldTransform; }
	glm::mat4& getTransform() { return m_worldTransform; }

	const glm::mat4& getProjectionMatrix() const; 
	void SetProjectionMatric(glm::mat4 projectionMatrix);

private:
	glm::mat4 ProjectionMatrix = glm::mat4(1);
	bool m_HasSetProjectionMatrix = false; 

};