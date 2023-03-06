#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Main.h"
#include "inputHandler.h"
#include "Exceptions.h"
#include "Draw.h"
#include "Shaders.h"

using namespace p3d;

p3d::Polygon *triangle;

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

        glfwSwapBuffers(window);
        
        // check and call events and swap the buffers
        glfwPollEvents();
    }
}

int p3d::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        throw p3d::FailedGLFWException();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw p3d::FailedGLADException();
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };
    triangle = new p3d::Polygon(vertices);

    // compile shaders
    p3d::compileShaders();

    glViewport(0, 0, 800, 600);
    p3d::render(window);

    glfwTerminate();
    return 0;
}