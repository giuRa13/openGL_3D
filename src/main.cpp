#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"
#include "Floor.hpp"
#include "Light.hpp"
#include "Model.hpp"
#include <iostream>
#include <cmath>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#define SCR_WIDTH  1200
#define SCR_HEIGHT 720
static float clear_color[4] = { 0.02f, 0.08f, 0.09f, 1.0f};
Window mainWindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void userInput(GLFWwindow* window);
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); 
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void RenderImGuiWindow();
//void LightImGui();

glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

//static float color_value[3] = { 1.0f ,1.0f , 1.0f };
//static float rotate_value[3] = { 1.0f,1.0f,1.0f };
static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float angle = -55.0f;
//static bool isTexture = false;
//static bool isColor = false;

static float material_specular[3] = {0.5f, 0.5f, 0.5f};
static float material_shininess = {64.0f};

Camera camera(glm::vec3(0.0f, 1.0f, 7.0f));

int main()
{
	mainWindow = Window(SCR_WIDTH, SCR_HEIGHT);
	mainWindow.Initialize();
	glfwSetFramebufferSizeCallback(mainWindow.getWindow(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(mainWindow.getWindow(), mouse_cursor_position);
    glfwSetScrollCallback(mainWindow.getWindow(), mouse_scroll_callback);

	Light light;
	light.SetSpeed(0.1f);

	Shader lightShader;
	lightShader.Create("../shaders/lightCube.vert", "../shaders/lightCube.frag");
	Shader myShader;
	myShader.Create("../shaders/default.vert", "../shaders/default.frag");
	//myShader.Create("../shaders/default.vert", "../shaders/lights.frag");

	std::vector<std::unique_ptr<Object>> objects;
	objects.push_back(std::make_unique<Cube>("../textures/container2.png"));
	objects.back()->GetTransform().SetPosition(0.0f, 0.25f, 0.0f);
	objects.back()->GetTransform().SetRotation(0.0f, 15.0f, 0.0f);
	objects.back()->GetTransform().SetScale(0.5f, 0.5f, 0.5f);

	objects.push_back(std::make_unique<Cube>("../textures/wood1.png"));
	objects.back()->GetTransform().SetPosition(-0.75f, 0.25f, -1.0f);
	objects.back()->GetTransform().SetRotation(0.0f, 30.0f, 0.0f);
	objects.back()->GetTransform().SetScale(0.5f, 0.5f, 0.5f);

	objects.push_back(std::make_unique<Floor>("../textures/Tile_20.png"));
	objects.back()->GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
	objects.back()->GetTransform().SetRotation(0.0f, 0.0f, 0.0f);
	objects.back()->GetTransform().SetScale(0.75f, 0.75f, 0.75f);

	objects.push_back(std::make_unique<Pyramid>("../textures/bricks_white.jpg"));
	objects.back()->GetTransform().SetPosition(-6.0f, 1.5f, -5.5f);
	objects.back()->GetTransform().SetRotation(270.0f, 0.0f, 0.0f);
	objects.back()->GetTransform().SetScale(2.0f, 2.0f, 2.0f);

	objects.push_back(std::make_unique<Pyramid>("../textures/bricks_yellow.jpg"));
	objects.back()->GetTransform().SetPosition(-4.0f, 1.0f, -4.0f);
	objects.back()->GetTransform().SetRotation(270.0f, 0.0f, 0.0f);
	objects.back()->GetTransform().SetScale(1.5f, 1.5f, 1.5f);

	std::vector<std::unique_ptr<Model>> models;
	models.push_back(std::make_unique<Model>("../models/girl.obj"));
	models.back()->GetTransform().SetPosition(4.5f, 1.5f, -5.5f);
	models.back()->GetTransform().SetScale(1.25f, 1.25f, 1.25f);

	models.push_back(std::make_unique<Model>("../models/Armchair.obj"));
	models.back()->GetTransform().SetPosition(4.5f, 0.0f, -1.5f);
	models.back()->GetTransform().SetRotation(0.0f, -40.0f, 0.0f);
	models.back()->GetTransform().SetScale(0.4f, 0.4f, 0.4f);

	models.push_back(std::make_unique<Model>("../models/ship/scene.gltf"));
	models.back()->GetTransform().SetPosition(-0.5f, 0.0f, -5.5f);
	models.back()->GetTransform().SetRotation(-90.0f, -23.0f, 0.0f);
	models.back()->GetTransform().SetScale(0.3f, 0.3f, 0.3f);


	while (!mainWindow.getShouldClose())
	{
		/* Update */
        userInput(mainWindow.getWindow());
		glfwPollEvents();		

        float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;

		////////////////////////////////////////////////////////////////
		/* Render */ 
		//glClearColor(0.1f, 0.2f, 0.3f, 1.0f); 
		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		light.LightImGui();
		mainWindow.CustomButtons();
		ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
		ImGui::ColorEdit4("Background Color", clear_color);
		//RenderImGuiWindow();
		if (mainWindow.ShowDemo)
			ImGui::ShowDemoWindow(&mainWindow.ShowDemo);


		myShader.use();
		light.SendToShader(myShader);

		myShader.setVec3("viewPos", camera.Position);

		myShader.setVec3("material.specular", material_specular[0], material_specular[1], material_specular[2]);
		myShader.setFloat("material.shininess", material_shininess);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		view = glm::mat4(1.0f);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		for(auto& object : objects)
			object->Render(myShader);

		for(auto& model : models)
			model->Draw(myShader);

		/*model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		myShader.setMat4("model", model);
		cube.Render(myShader);*/

		lightShader.use();
		light.Update(mainWindow.getWindow());
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		light.Render(lightShader);
		
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ////////////////////////////////////////////////////////////////

		mainWindow.swapBuffers();	
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	return 0;
}


void userInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	const float camera_speed = 1.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE) // Forward
		camera.ProcessKeyboard(FORWARD, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE) // Backward
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE) // Right
		camera.ProcessKeyboard(RIGHT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE) // Left
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_TRUE) // Up
		camera.ProcessKeyboard(UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_TRUE) // Down
		camera.ProcessKeyboard(DOWN, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_TRUE) 
		camera.ProcessKeyboard(TURN_LEFT, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_TRUE) 
		camera.ProcessKeyboard(TURN_RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_TRUE) 
		camera.ProcessKeyboard(TURN_UP, deltaTime);
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_TRUE) 
		camera.ProcessKeyboard(TURN_DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << "Poisiton :" << xpos << " " << ypos << std::endl;
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
	//std::cout << "Scroll offset : " << xoffset << " " << yoffset << std::endl;
}


/*void LightImGui()
{
	ImGui::Begin("Light test");
	ImGui::Text("FPS = %f", ImGui::GetIO().Framerate);

	//ImGui::SliderFloat3("Material Specular", material_specular, 0.0f, 1.0f);
	ImGui::SliderFloat("Material Shininess", &material_shininess, 0.0f, 600.f);
	ImGui::SliderInt("Light Attenuation", &light_power, 0, 10);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));

	ImGui::SliderFloat("Light Ambient", &ambient_Strenght, 0.0f, 1.0f);
	ImGui::ColorEdit3("Ambient Color", light_ambient);
	ImGui::SliderFloat("Light Diffuse", &diffuse_Strenght, 0.0f, 1.0f);
	ImGui::ColorEdit3("Diffuse Color", light_diffuse);
	ImGui::SliderFloat3("Light Specular", light_specular, 0.0f, 1.0f);

	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
	ImGui::ColorEdit4("Background Color", clear_color);

	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
	CustomButtons();

	ImGui::End();
}*/


/*void RenderImGuiWindow()
{
	ImGui::Begin("ImGui Window", nullptr,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	ImGui::Text("hello Dear ImGui");
	ImGui::SameLine();
	ImGui::Text(" | ");
	ImGui::SameLine();
	ImGui::Text("FPS = %f", ImGui::GetIO().Framerate);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));

	ImGui::DragFloat3("Scale value", scale_value, 0.1f, 0.1f, 5.0f);
	ImGui::SliderFloat3("Rotate value", rotate_value, 0.01f, 1.0f);
	ImGui::SliderAngle("Angle", &angle);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
	
	ImGui::SliderFloat3("Color value", color_value, 0.0f, 1.0f);
	ImGui::ColorEdit3("Color Edit", color_value);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
	
	ImGui::Checkbox("Texture", &isTexture);
	ImGui::SameLine();
	ImGui::Checkbox("Color", &isColor);
	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));

	CustomButtons();
		
	ImGui::End();
}*/
