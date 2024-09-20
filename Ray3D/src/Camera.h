#pragma once

#include <iostream>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };


class Camera
{
private:
	glm::mat4 viewMatrix;

	glm::vec3 worldUp, pos, front, up, right;

	GLfloat pitch, yaw, roll;
	GLfloat moveSpeed, sensitivity;


public:
	//Constructor & Destructor
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 world_up);
	virtual ~Camera();
	
	//Accessors
	const glm::mat4 GetViewMatrix();
	inline const glm::vec3 GetPosition() const	{ return this->pos; }
	
	//Player Input
	void MouseInput(const float& delta_time, const double& offset_x, const double& offset_y);
	void Move(const float& delta_time, const int direction);
	void UpdateInput(const float& delta_time, const int direction, const double& offset_x, const double& offset_y);


private:
	void UpdateCameraVectors();
};