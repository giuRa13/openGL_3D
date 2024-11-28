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
    void SendToShader(Shader &shader);

    void LightImGui();


private:
    GLuint VBO, VAO;

    glm::mat4 m_model;
    glm::vec3 m_position;
    GLfloat m_speed;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    float ambient_Strenght;
    float diffuse_Strenght;
    int light_attenuation;
     
};
