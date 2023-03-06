#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace p3d {
	GLFWwindow* init();
	void render(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void renderBackground(float* rgba);
}
