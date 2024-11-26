#include "Texture.hpp"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
    textureID = 0;
};

bool Texture::load_texture(const char* fileLocation)
{
	//unsigned int textureID;
	int width, height, nrChannels;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);

	//int width, height, nrChannels;
	unsigned char* data = stbi_load(fileLocation, &width, &height, &nrChannels, 0);

	if (data)
	{
		// Note it's a better way to see that what our file is like png, jpg or jpeg ?
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		if (nrChannels == 3) // jpg file
			format = GL_RGB;
		if (nrChannels == 4) // png file
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture\n";
        return false;
	}

	stbi_image_free(data);

	//return textureID;
    return true;
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, textureID); 
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void Texture::UseTexture()
{
    glActiveTexture(GL_TEXTURE0);
}

void Texture::UseTexture2()
{
    glActiveTexture(GL_TEXTURE1);
}

void Texture::ClearTexture()
{
    glDeleteTextures(1, &textureID);
}

Texture::~Texture()
{
    ClearTexture();
}

 GLuint Texture::GetTextureID()
 {
    return textureID;
 }