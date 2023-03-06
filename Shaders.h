#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace p3d {
	void errHandleCompileShaders(GLuint check);

	void errHandleLinkShaders(GLuint check);

	void compileShaders();

	void createShaderProgram(GLuint vShader, GLuint fShader);
}