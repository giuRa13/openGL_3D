#pragma once

#include "Texture.hpp"
#include "Shader.hpp"
#include "Object.hpp"
#include <glm/glm.hpp>

class Floor : public Object
{

public:
    Floor(const char* file);
    ~Floor();

    void Update() override{};
    void Render(Shader &shader) override;


private:
    GLuint VBO, VAO, IBO;
    //GLsizei indexCount;

    Texture m_texture;
    const char* fileLocation;

};