#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace p3d {
	class Polygon {
		private:
			GLuint VBO;
			GLuint VAO;
			
			float* verts;
		public:
			void render();
			Polygon(float* v);
	};
}