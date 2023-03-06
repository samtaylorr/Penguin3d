#pragma once
#include "Shaders.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


GLuint shaderProgram;

void p3d::errHandleCompileShaders(GLuint check) {
	int  success;
	char infoLog[512];
	glGetShaderiv(check, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(check, 512, NULL, infoLog);
		// TODO: Create exception
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void p3d::errHandleLinkShaders(GLuint check) {
	int  success;
	char infoLog[512];
	glGetProgramiv(check, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(check, 512, NULL, infoLog);
		// TODO: Create exception
		std::cout << "ERROR::SHADER::VERTEX::CREATION_FAILED\n" << infoLog << std::endl;
	}
}

void p3d::compileShaders() {
	// COMPILE VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	errHandleCompileShaders(vertexShader);


	// COMPILE FRAGMENT SHADER
	GLuint fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	errHandleCompileShaders(fragmentShader);

	createShaderProgram(vertexShader, fragmentShader);
}

void p3d::createShaderProgram(GLuint vShader, GLuint fShader)
{
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	errHandleLinkShaders(shaderProgram);

	glUseProgram(shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}