#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 world_up)
	: pos(position), worldUp(world_up), up(world_up)
{
	this->viewMatrix = glm::mat4(1.0f);

	this->right = glm::vec3(0.0f);
	
	this->pitch = 0.0f;
	this->yaw = -90.0f;
	this->roll = 0.0f;

	this->moveSpeed = 5.0f;
	this->sensitivity = 10.0f;

	this->UpdateCameraVectors();
}

Camera::~Camera()
{
}


const glm::mat4 Camera::GetViewMatrix()
{
	this->UpdateCameraVectors();

	this->viewMatrix = glm::lookAt(this->pos, this->pos + this->front, this->up);

	return this->viewMatrix;
}


//	PLAYER INPUT    //
//***************************************
void Camera::Move(const float& delta_time, const int direction)
{
	switch (direction)
	{
	case FORWARD:
		this->pos += this->front * this->moveSpeed * delta_time;
		break;
		
	case BACKWARD:
		this->pos -= this->front * this->moveSpeed * delta_time;
		break;

	case LEFT:
		this->pos -= this->right * this->moveSpeed * delta_time;
		break;

	case RIGHT:
		this->pos += this->right * this->moveSpeed * delta_time;
		break;

	default:
		break;
	}
}

void Camera::MouseInput(const float& delta_time, const double& offset_x, const double& offset_y)
{
	this->pitch -= static_cast<GLfloat>(offset_y) * (this->sensitivity * 2) * delta_time;
	this->yaw	+= static_cast<GLfloat>(offset_x) * this->sensitivity * delta_time;

	//Limiting pitch
	if (this->pitch > 80.0f)
		this->pitch = 80.0f;
	else if (this->pitch < -80.0f)
		this->pitch = -80.0f;

	//Limiting yaw
	if (this->yaw > 360.0f || this->yaw < -360.0f)
		this->yaw = 0.0f;
}

void Camera::UpdateInput(const float& delta_time, const int direction, const double& offset_x, const double& offset_y)
{
	this->MouseInput(delta_time, offset_x, offset_y);
}
//***************************************


/****************************************
* To understand the maths, check out this page:
* https://learnopengl.com/Getting-started/Camera
****************************************/
void Camera::UpdateCameraVectors()
{
	//Calculating the front vector (camera facing direction)
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);

	//Calculating the right vector (camera's right direction)
	//Cross product of front & up gives a direction perpendicular to both i.e. right
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));

	//Calculating the up direction (camera's up direction)
	//Cross product of right & front gives up
	this->up = glm::normalize(glm::cross(this->right, this->front));
}