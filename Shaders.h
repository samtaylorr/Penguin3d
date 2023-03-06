#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Create shader class
// Return shaderProgram
// Pass shaderProgram into a render method

namespace p3d {

	struct rgba {
	public:
		float r;
		float g;
		float b;
		float a;
		rgba(float r, float g, float b, float a);
		std::string r_toString();
		std::string g_toString();
		std::string b_toString();
		std::string a_toString();
	};

	class Shader {
	public:
		Shader();
		GLuint getShaderProgram();

	private:
		GLuint shaderProgram;

		std::string vertexShaderSource, fragmentShaderSource;

		void errHandleCompileShaders(GLuint check);

		void errHandleLinkShaders(GLuint check);

		void compileShaders();

		void createShaderProgram(GLuint vShader, GLuint fShader);
	};
}