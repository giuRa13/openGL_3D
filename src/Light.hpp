#pragma once

#include "Shader.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Light
{

public:
    Light();
    ~Light();

    void SetSpeed(GLfloat speed);
    glm::vec3 getPosition() { return m_position; }

    void Update(GLFWwindow *window);
    void Render(Shader &shader);


private:
    GLuint VBO, VAO;

    glm::vec3 m_position;
    GLfloat m_speed;

};
