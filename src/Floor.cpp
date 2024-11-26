#include "Floor.hpp"
#include <glad/glad.h>


Floor::Floor(const char* file)
{
    float vertices[] =
    {
        -10.0f, 0.0f, -10.0f,	1.0f,1.0f,1.0f,		0.0f,0.0f,		0.0f, 1.0f, 0.0f,
        -10.0f, 0.0f,  10.0f,	1.0f,1.0f,1.0f,		0.0f,10.0f,		0.0f, 1.0f, 0.0f,
        10.0f, 0.0f, -10.0f,	1.0f,1.0f,1.0f,		10.0f,0.0f,		0.0f, 1.0f, 0.0f,

        10.0f, 0.0f, -10.0f,	1.0f,1.0f,1.0f,		10.0f,0.0f,		0.0f, 1.0f, 0.0f,
        -10.0f, 0.0f,  10.0f, 	1.0f,1.0f,1.0f,		0.0f,10.0f,		0.0f, 1.0f, 0.0f,
        10.0f, 0.0f,  10.0f,	1.0f,1.0f,1.0f,		10.0f,10.0f, 	0.0f, 1.0f, 0.0f
    };
    GLuint floorIndices[] =
    {
        0, 1, 2,
        0, 2, 3
    };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//Color 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//TexCoord
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
    //Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    
    fileLocation = file;
    m_texture.load_texture(fileLocation);

}

Floor::~Floor()
{
}

void Floor::Render(Shader &shader)
{
	glBindVertexArray(VAO);

    //shader.setInt("texture1", 0);
    shader.setInt("material.diffuse", 0);
    m_texture.Bind();
	
    glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
    m_texture.Unbind();

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Floor::Update()
{

}