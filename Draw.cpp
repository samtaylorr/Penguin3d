#pragma once
#include "Draw.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shaders.h"
#include <vector>
#include <array>

p3d::Triangle::Triangle(float v[9], GLuint shaderProgram, std::vector<GLfloat> color) {

	float vertices[9];
	this->color = color;
	this->shaderProgram = shaderProgram;

	for (int i = 0; i < 9; i++) { vertices[i] = v[i]; }

	GLuint indices[] = {
		0,1,2
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void p3d::Triangle::render() {
	glUseProgram(this->shaderProgram);
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");
	glUniform4f(vertexColorLocation, color[0], color[1], color[2], color[3]);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}