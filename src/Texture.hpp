#pragma once

#include <glad/glad.h>


class Texture
{

public:
    Texture();
    ~Texture();

    bool load_texture(const char* fileLocation);
    void UseTexture();
    void UseTexture2();
    void Bind() const;
    void Unbind();
    void ClearTexture();

    GLuint GetTextureID();


private:
    GLuint textureID;
    const char* filepath;
    
};