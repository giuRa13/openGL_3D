#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.hpp"


class Object
{

public:
    Object();
    virtual ~Object() = default;

    void SetPosition(GLfloat x, GLfloat y, GLfloat z);
    void SetRotation(GLfloat pitch, GLfloat yaw, GLfloat roll);
    void SetScale(GLfloat x, GLfloat y, GLfloat z);

    virtual void Update() = 0;
    virtual void Render(Shader& shader);

private:
    glm::mat4 m_model;
   
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
};