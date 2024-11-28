#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include "Object.hpp"
#include <glm/glm.hpp>


class Cube : public Object
{

public:
    Cube(const char* file);
    Cube(const char* diffuse, const char* specular);
    ~Cube();

    void Update() override {}
    void Render(Shader &shader) override;


private:
    GLuint VBO, VAO;
    Texture m_texture;
    Texture m_diffuse;
    const char* fileLocation;
    const char* specularMap;
    bool b_specular = false;

};
