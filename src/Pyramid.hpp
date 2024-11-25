#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Pyramid
{

public:
    Pyramid(const char* file);
    ~Pyramid();

    void Update();
    void Render(Shader &shader);


private:
    unsigned int VBO, VAO;
    Texture m_texture;
    const char* fileLocation;

    glm::mat4 m_model;
    glm::vec3 m_position;


};
