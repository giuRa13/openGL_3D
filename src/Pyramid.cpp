#include "Pyramid.hpp"
#include <glad/glad.h>


Pyramid::Pyramid(const char* file)
{
    float vertices[] =
    {
        /* Bottom Position */	
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
        /* Front Position */	
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.5f,		0.0f, 0.0f, 1.0f,		0.5f, 1.0f,		0.0f, -1.0f, 0.0f,
        /* Back Position */ 	
        -0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.5f,		0.0f, 0.0f, 1.0f,		0.5f, 1.0f,		0.0f, 1.0f, 0.0f,
        /* Left Position */ 	
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f,		0.0f, 0.0f, 1.0f,		0.5f, 1.0f,		-1.0f, 0.0f, 0.0f,
        /* Right Position */ 	
        0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f,		0.0f, 0.0f, 1.0f,		0.5f, 1.0f,		1.0f, 0.0f, 0.0f,
    };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	/* Position Attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* Color Attribute*/
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/* Texture Attribute */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    fileLocation = file;
    m_texture.load_texture(fileLocation);


}

Pyramid::~Pyramid()
{

}

void Pyramid::Render(Shader &shader)
{
    Object::Render(shader);

	glBindVertexArray(VAO);
	
    //shader.setInt("material.diffuse", 0);
    m_texture.Bind();

    glDrawArrays(GL_TRIANGLES, 0, 18);

    glBindVertexArray(0);
    m_texture.Unbind();

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

