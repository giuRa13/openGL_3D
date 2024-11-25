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
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#define SCR_WIDTH  1200
#define SCR_HEIGHT 720
Window mainWindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void userInput(GLFWwindow* window);
void mouse_cursor_position(GLFWwindow* window, double xpos, double ypos); 
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void RenderImGuiWindow();
void CustomButtons();
void SimpleImGui();

glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;
//glm::vec3 lightPos = glm::vec3(1.0f, 1.0f, -1.0f);
//glm::vec3 myPos = glm::vec3(0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = float(SCR_WIDTH) / 2.0f;
float lastY = float(SCR_HEIGHT) / 2.0f;
bool isFirstMouse = true;

static float scale_value[3] = { 1.0f ,1.0f , 1.0f };
static float color_value[3] = { 1.0f ,1.0f , 1.0f };
static float rotate_value[3] = { 1.0f,1.0f,1.0f };
static float angle = -55.0f;
static bool isTexture = false;
static bool isColor = false;
bool ShowDemo = false;
static float shininess = 32.0f;
static float ambientStrength = 0.2f;
static float light_color[3] = { 1.0f ,1.0f , 1.0f };


int main()
{
	mainWindow = Window(SCR_WIDTH, SCR_HEIGHT);
	mainWindow.Initialize();
	glfwSetFramebufferSizeCallback(mainWindow.getWindow(), framebuffer_size_callback);
    //glfwSetCursorPosCallback(mainWindow.getWindow(), mouse_cursor_position);
    glfwSetScrollCallback(mainWindow.getWindow(), mouse_scroll_callback);


	Cube cube("../textures/wood2.png");
	Pyramid pyramid("../textures/bricks_yellow.jpg");
	Pyramid pyramid2("../textures/bricks_grey.jpg");
	Floor floor("../textures/g1572.png");

	Light light;
	light.SetSpeed(0.1f);

	Shader lightShader;
	lightShader.Create("../shaders/light.vert", "../shaders/light.frag");
	Shader myShader;
	myShader.Create("../shaders/default.vert", "../shaders/default.frag");


	while (!mainWindow.getShouldClose())
	{
		/* Update */
        userInput(mainWindow.getWindow());
		glfwPollEvents();

        float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;

        float xValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float yValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f
		float zValue = std::sin(time) / 2.0f + 0.5f; // 0.0f - 1.0f

		float radius = 5.0f;
		float camX = sin(time) * radius;
		float camZ = cos(time) * radius;

		////////////////////////////////////////////////////////////////
		/* Render */
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//RenderImGuiWindow();
		SimpleImGui();
		if (ShowDemo)
			ImGui::ShowDemoWindow(&ShowDemo);

		myShader.use();
		myShader.setVec3("lightColor", light_color[0], light_color[1], light_color[2]);
		myShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
		myShader.setVec3("lightPos", light.getPosition());
		myShader.setVec3("viewPos", camera.Position);
		myShader.setFloat("shininess", shininess);
		myShader.setFloat("ambientStrength", ambientStrength);
		//myShader.setVec3("colors", color_value[0], color_value[1], color_value[2]);
		//myShader.setBool("isTexture", isTexture);
		//myShader.setBool("isColor", isColor);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
		myShader.setMat4("projection", projection);

		view = glm::mat4(1.0f);
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		view = camera.GetViewMatrix();
		myShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		myShader.setMat4("model", model);
		cube.Render(myShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f));
		model = glm::translate(model, glm::vec3(-2.5f, -1.0f, -2.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.5f, 0.5f, 0.5f));
		myShader.setMat4("model", model);
		pyramid.Render(myShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f));
		model = glm::translate(model, glm::vec3(-2.5f, -0.25f, -2.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.2f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.5f, 0.5f, 0.5f));
		myShader.setMat4("model", model);
		pyramid2.Render(myShader);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		myShader.setMat4("model", model);
		floor.Render(myShader);
		

		lightShader.use();
		light.Update(mainWindow.getWindow());
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, light.getPosition());
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMat4("model", model);
		light.Render(lightShader);
		

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ////////////////////////////////////////////////////////////////

		//glfwSwapBuffers(mainWindow.getWindow());
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

	/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myPos.y += 0.1f;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myPos.y -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myPos.x += 0.1f;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myPos.x -= 0.1f;*/
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


void SimpleImGui()
{
	ImGui::Begin("Light test");
	ImGui::Text("FPS = %f", ImGui::GetIO().Framerate);

	ImGui::SliderFloat("shininess", &shininess, 0.0f, 600.0f);
	ImGui::SliderFloat("Ambient Value", &ambientStrength, 0.1f, 1.0f);
	ImGui::SliderFloat3("Light Color", light_color, 0.01f, 1.0f);
	ImGui::ColorEdit3("Color Edit", light_color);

	ImGui::InvisibleButton("##space", ImVec2(1.f,12.f));
	CustomButtons();

	ImGui::End();
}


void RenderImGuiWindow()
{
	ImGui::Begin("ImGui Window", nullptr/*,
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse*/);

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
}

void CustomButtons()
{
	std::string btn1 = "Theme";
	std::string btn2 = "Default";
	std::string btn3 = "Demo";
	auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth   = ImGui::CalcTextSize(btn1.c_str()).x + 
		ImGui::CalcTextSize(btn2.c_str()).x +
		ImGui::CalcTextSize(btn3.c_str()).x + 40;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	if (ImGui::Button(btn3.c_str()))
		ShowDemo = true;
	ImGui::SameLine();
	if(ImGui::Button(btn1.c_str()))
        (mainWindow.changeTheme ? mainWindow.set_theme1() : mainWindow.set_theme2());
    ImGui::SameLine();
    if(ImGui::Button(btn2.c_str()))
    {
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
		style.WindowRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.f;
		style.ChildRounding = 0.f;
    }
}