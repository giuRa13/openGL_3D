#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdio.h>

class Window
{

public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);
    ~Window();

    int Initialize();

    GLFWwindow* getWindow() { return mainWindow; }
    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }
    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { return glfwSwapBuffers(mainWindow); }

    void GetOpenGLVersionInfo();
    void set_theme1();
    void set_theme2();
    bool changeTheme = false;


private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

};