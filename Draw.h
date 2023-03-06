#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"

namespace p3d {
	class Triangle {
		private:
			GLuint VBO, VAO, EBO;
			std::vector<float> color;
		public:
			void render();
			Triangle(float v[9], std::vector<GLfloat> color);
	};
}