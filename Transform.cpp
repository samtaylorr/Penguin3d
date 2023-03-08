#include "Transform.h"
#include <iostream>
#include <glad/glad.h>
#include "Shader.h"
#include <GLFW/glfw3.h>

p3d::Transform::Transform(p3d::Shader* s) {
	this->shader = s;
	shader->use();

	Matrix4 trans = Matrix4(1.0f);
	this->position = new Vector3(0.0f, 0.0f, 0.0f);
	this->sendToShader(trans);
}

void p3d::Transform::sendToShader(Matrix4 matrix) {
	GLuint transformLoc = glGetUniformLocation(this->shader->ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void p3d::Transform::Translate(glm::vec3* vector) {
	Matrix4 trans = Matrix4(1.0f);
	Vector3* vec = new Vector3(*this->position + *vector);
	trans = glm::translate(trans, *vec);
	this->sendToShader(trans);
	delete vec;
}