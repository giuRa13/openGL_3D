#include "Light.hpp"
#include <glad/glad.h>


Light::Light()
{
    float vertices[] =
    {
        /*Top Position*/		
        -0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		
        /* Bottom Position */		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Left Position */		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        -0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        -0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Right Position */	
        0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Back Position */		
        -0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Front Position */
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		

    };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    m_position = glm::vec3(0.0f, 2.0f, -2.0f);
}


void Light::Render(Shader &shader)
{

	glBindVertexArray(VAO);
	
    glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Light::SetSpeed(GLfloat speed)
{
    m_speed = speed;
}

void Light::Update(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_TRUE)
		m_position.x -= m_speed;
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_TRUE)
		m_position.x += m_speed;
    else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_TRUE)
		m_position.y += m_speed;
	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_TRUE)
		m_position.y -= m_speed;
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_TRUE)
		m_position.z += m_speed;
	else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_TRUE)
		m_position.z -= m_speed;
}

Light::~Light()
{
}