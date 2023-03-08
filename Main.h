#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Pawn.h"

namespace p3d {
	GLFWwindow* init();
	void render(GLFWwindow* window, Pawn* pawn);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void renderBackground(float* rgba);
}
