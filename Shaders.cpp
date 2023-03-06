#pragma once
#include "Shaders.h"
#include <iostream>
#include <string>

p3d::Shader::Shader() {

	vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos; // the position variable has attribute position 0\n"

		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor\n"
		"}\0";

	fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"

		"uniform vec4 Color; // we set this variable in the OpenGL code.\n"

		"void main()\n"
		"{\n"
		"	FragColor = Color;\n"
		"}\0";

	this->compileShaders();
}

void p3d::Shader::errHandleCompileShaders(GLuint check) {
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

void p3d::Shader::errHandleLinkShaders(GLuint check) {
	int  success;
	char infoLog[512];
	glGetProgramiv(check, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(check, 512, NULL, infoLog);
		// TODO: Create exception
		std::cout << "ERROR::SHADER::VERTEX::CREATION_FAILED\n" << infoLog << std::endl;
	}
}

void p3d::Shader::compileShaders() {
	// COMPILE VERTEX SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const char* v_str = vertexShaderSource.c_str();

	glShaderSource(vertexShader, 1, &v_str, NULL);
	glCompileShader(vertexShader);

	errHandleCompileShaders(vertexShader);


	// COMPILE FRAGMENT SHADER
	GLuint fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* f_str = fragmentShaderSource.c_str();

	glShaderSource(fragmentShader, 1, &f_str, NULL);
	glCompileShader(fragmentShader);

	errHandleCompileShaders(fragmentShader);

	createShaderProgram(vertexShader, fragmentShader);
}

void p3d::Shader::createShaderProgram(GLuint vShader, GLuint fShader)
{
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	errHandleLinkShaders(shaderProgram);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

GLuint p3d::Shader::getShaderProgram() {
	return shaderProgram;
}

p3d::rgba::rgba(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

std::string p3d::rgba::r_toString()
{
	return std::to_string(this->r);
}

std::string p3d::rgba::g_toString()
{
	return std::to_string(this->g);
}

std::string p3d::rgba::b_toString()
{
	return std::to_string(this->b);
}

std::string p3d::rgba::a_toString()
{
	return std::to_string(this->a);
}
