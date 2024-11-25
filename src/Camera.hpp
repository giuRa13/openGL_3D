#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
    TURN_RIGHT,
    TURN_LEFT,
    TURN_UP,
    TURN_DOWN
};

const float YAW = -90.0f;
const float PITCH = -0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera 
{

public:
	//Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	glm::vec3 Right;
	// Eular Angles
	float Yaw;
	float Pitch;
	//Camera Options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
        float yaw = YAW, float pitch = PITCH)
		:   Front(glm::vec3(0.0f, 0.0f, -1.0f)), 
            MovementSpeed(SPEED), 
            MouseSensitivity(SENSITIVITY), 
            Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return lookAt(this->Position, this->Position + this->Front, this->Up);
	}

	void ProcessMouseMovement(float xoffset, float yoffset)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		if (this->Pitch >= 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch <= -89.0f)
			this->Pitch = -89.0f;

		updateCameraVectors();
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		const float velocity = this->MovementSpeed * deltaTime;

		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == UP)
			this->Position += this->Up * velocity;
		if (direction == DOWN)
			this->Position -= this->Up * velocity;

        if (direction == TURN_RIGHT)
			this->Yaw += 1.0f;
		else if(direction == TURN_LEFT)
			this->Yaw -= 1.0f;
        if (direction == TURN_UP)
			this->Pitch += 1.0f;
		else if(direction == TURN_DOWN)
			this->Pitch -= 1.0f;

        updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		this->Zoom -= float(yoffset);

		if (Zoom >= 45.0f)
			Zoom = 45.0f;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
	}


private:
	void updateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = std::cos(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		direction.y = std::sin(glm::radians(this->Pitch));
		direction.z = std::sin(glm::radians(this->Yaw)) * std::cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(direction);

		// Also re-calculate for Right and Up vectors
		this->Right = normalize(cross(this->Front, this->WorldUp));
		this->Up = normalize(cross(this->Right, this->Front));
	}
};