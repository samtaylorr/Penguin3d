#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Main.h"
#include "inputHandler.h"
#include "Exceptions.h"
#include "Draw.h"
#include "Shaders.h"
#include <vector>
#include <array>

using namespace p3d;

p3d::Triangle* triangle;
p3d::Triangle* triangle2;

void p3d::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void p3d::renderBackground(float* rgba)
{
    glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
    p3d::init();

    GLFWwindow* window = p3d::init();

    Shader* shader = new Shader();

    std::vector<GLfloat> yellow = { 1.0f, 1.0f, 0.2f, 1.0f };
    std::vector<GLfloat> red = { 1.0f, 0.1f, 0.1f, 1.0f };

    triangle = new p3d::Triangle(new float[9] {
        -0.9f, -0.5f, 0.0f,  // left 
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top 
        }, shader->getShaderProgram(), yellow);

    triangle2 = new p3d::Triangle(new float[9] {
        0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top 
        }, shader->getShaderProgram(), red);

    p3d::render(window);

    glfwTerminate();
    return 0;
}

void p3d::render(GLFWwindow* window) {
    
    float rgba[] = {0.2f, 0.2f, 0.3f, 1.0f};
    float* rgba_ptr = rgba;
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        p3d::processInput(window);

        // rendering events
        p3d::renderBackground(rgba_ptr);
        triangle->render();
        triangle2->render();

        glfwSwapBuffers(window);
        
        // check and call events and swap the buffers
        glfwPollEvents();
    }
}

GLFWwindow* p3d::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Penguin3D", NULL, NULL);
    if (window == NULL)
    {
        throw p3d::FailedGLFWException();
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw p3d::FailedGLADException();
        glfwTerminate();
        return NULL;
    }

    glViewport(0, 0, 1280, 720);

    return window;
}