#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include "Object.hpp"
#include <glm/glm.hpp>

class Pyramid : public Object
{

public:
    Pyramid(const char* file);
    ~Pyramid();

    void Update() override {}
    void Render(Shader &shader) override;


private:
    unsigned int VBO, VAO;
    Texture m_texture;
    const char* fileLocation;

};
