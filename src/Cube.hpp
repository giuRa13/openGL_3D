#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>

class Cube
{

public:
    Cube(const char* file);
    Cube(const char* diffuse, const char* specular);
    ~Cube();

    void Update();
    void Render(Shader &shader);


private:
    GLuint VBO, VAO;
    Texture m_texture;
    Texture m_diffuse;
    const char* fileLocation;
    const char* specularMap;
    bool b_specular = false;

    glm::mat4 m_model;
    glm::vec3 m_position;


};
