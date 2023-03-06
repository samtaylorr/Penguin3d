#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Main.h"
#include "inputHandler.h"
#include "Exceptions.h"
#include "Draw.h"
#include "Shader.h"
#include <vector>
#include <array>

using namespace p3d;

p3d::Triangle* triangle;

Shader* shader;


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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    
    GLFWwindow* window = p3d::init();

    Shader s("vertex_shader.glsl", "fragment_shader.glsl"); // you can name your shader files however you like
    shader = &s;
    float v3[3]  = {0.5f, 0.2f, 0.5f};

    triangle = new p3d::Triangle(new float[18] {
        // positions                    //colors
         0.5f, -0.5f, 0.0f,             1.0f, 0.0f, 0.0f,     // left
        -0.5f, -0.5f, 0.0f,             0.0f, 1.0f, 0.0f,     // right
         0.0f,  0.5f, 0.0f,             0.0f, 0.0f, 1.0f      // top 
    });

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
        shader->use();
        triangle->render();

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Penguin3D", NULL, NULL);
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

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    return window;
}