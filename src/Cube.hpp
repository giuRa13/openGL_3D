#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Cube
{

public:
    Cube(const char* file);
    ~Cube();

    void Update();
    void Render(Shader &shader);


private:
    GLuint VBO, VAO;
    Texture m_texture;
    const char* fileLocation;

    glm::mat4 m_model;
    glm::vec3 m_position;


};
