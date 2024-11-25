#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Floor
{

public:
    Floor(const char* file);
    ~Floor();

    void Update();
    void Render(Shader &shader);


private:
    GLuint VBO, VAO, IBO;
    GLsizei indexCount;

    Texture m_texture;
    const char* fileLocation;

    glm::mat4 m_model;
    glm::vec3 m_position;


};