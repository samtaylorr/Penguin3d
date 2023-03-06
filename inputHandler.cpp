#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "inputHandler.h"

void p3d::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
