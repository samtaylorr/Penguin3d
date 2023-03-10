#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <iostream>
#include "Main.h"
#include "inputHandler.h"
#include "Exceptions.h"
#include "Mesh.h"
#include "Shader.h"
#include "PawnFactory.h"

using namespace p3d;
Shader* shader;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    GLFWwindow* window = p3d::init();
     // you can name your shader files however you like

    PawnFactory* pawnFactory = new PawnFactory();
    Pawn* pawn = pawnFactory->CreatePawn();

    delete pawnFactory;

    p3d::render(window, pawn);

    glfwTerminate();
    return 0;
}

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

void p3d::render(GLFWwindow* window, Pawn* pawn) {
    
    float rgba[] = {0.2f, 0.2f, 0.3f, 1.0f};
    float* rgba_ptr = rgba;
    Vector3* vector3 = new Vector3(0.5f, -0.5f, 0.0f);
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        p3d::processInput(window);

        // rendering events
        p3d::renderBackground(rgba_ptr);

        // this currently throws an error
        // TODO: Create GetComponent in Pawn
        // GetComponent Mesh
        // Attach shader class to Mesh so that it doesn't have to pass it through
        pawn->GetTransform()->Translate(vector3);
        pawn->GetMesh()->render();
        
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