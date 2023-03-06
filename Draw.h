#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace p3d {
	class Triangle {
		private:
			GLuint VBO, VAO, EBO, shaderProgram;
			std::vector<float> color;
		public:
			void render();
			Triangle(float v[9], GLuint shaderProgram, std::vector<GLfloat> color);
	};
}