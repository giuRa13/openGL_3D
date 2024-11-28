#include "Light.hpp"
#include "Window.hpp"
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


Light::Light()
{
    float vertices[] =
    {
        /*Top Position*/		
        -0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 0.0f, 0.0f,		
        /* Bottom Position */		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f,-0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Left Position */		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        -0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        -0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Right Position */	
        0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Back Position */		
        -0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f, 0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f, 0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f, 0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        /* Front Position */
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		
        0.5f,-0.5f,-0.5f,		0.0f, 1.0f, 0.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        0.5f,-0.5f, 0.5f,		0.0f, 0.0f, 1.0f,		
        -0.5f,-0.5f, 0.5f,		1.0f, 1.0f, 0.0f,		
        -0.5f,-0.5f,-0.5f,		1.0f, 0.0f, 0.0f,		

    };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    m_position = glm::vec3(0.0f, 2.0f, -2.0f);
    m_ambient = glm::vec3(1.0f);
    m_diffuse = glm::vec3(1.0f);
    m_specular = glm::vec3(1.0f);
    ambient_Strenght = 0.1f;
    diffuse_Strenght = 0.5f;
    light_attenuation = 1;
}

void Light::SendToShader(Shader &shader)
{
    shader.setVec3("light.position", m_position);
	shader.setVec3("light.ambient", m_ambient.x *ambient_Strenght, m_ambient.y*ambient_Strenght, m_ambient.z*ambient_Strenght);
	shader.setVec3("light.diffuse",m_diffuse.x*diffuse_Strenght, m_diffuse.y*diffuse_Strenght, m_diffuse.z*diffuse_Strenght);
	shader.setVec3("light.specular",m_specular.x, m_specular.y, m_specular.z);
	shader.setFloat("light.constant", 1.0f);
	shader.setFloat("light.linear", 0.09f);
	shader.setFloat("light.quadratic", 0.032f);
	shader.setInt("lightPower", light_attenuation);
}

void Light::Render(Shader &shader)
{
    shader.setMat4("model", m_model);
    
	glBindVertexArray(VAO);
	
    glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);

    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Light::SetSpeed(GLfloat speed)
{
    m_speed = speed;
}

void Light::Update(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_TRUE)
		m_position.x -= m_speed;
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_TRUE)
		m_position.x += m_speed;
    else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_TRUE)
		m_position.y += m_speed;
	else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_TRUE)
		m_position.y -= m_speed;
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_TRUE)
		m_position.z += m_speed;
	else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_TRUE)
		m_position.z -= m_speed;


    m_model = glm::mat4( 1.0f);
    m_model = glm::translate( m_model, m_position);
    m_model = glm::scale(m_model, glm::vec3(0.2f));
}

Light::~Light()
{
}

void Light::LightImGui()
{
	ImGui::Begin("Light test");
	ImGui::Text("FPS = %f", ImGui::GetIO().Framerate);

	//ImGui::SliderFloat3("Material Specular", material_specular, 0.0f, 1.0f);
	//ImGui::SliderFloat("Material Shininess", &material_shininess, 0.0f, 600.f);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));

	ImGui::SliderFloat("Light Ambient", &ambient_Strenght, 0.0f, 1.0f);
	ImGui::ColorEdit3("Ambient Color", &m_ambient.x);
	ImGui::SliderFloat("Light Diffuse", &diffuse_Strenght, 0.0f, 1.0f);
	ImGui::ColorEdit3("Diffuse Color", &m_diffuse.x);

    ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
    ImGui::SliderInt("Light Attenuation", &light_attenuation, 0, 10);
	ImGui::SliderFloat3("Light Specular", &m_specular.x, 0.0f, 1.0f);

	ImGui::End();
}