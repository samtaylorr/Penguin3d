#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include "Component.h"

namespace p3d {
	class Mesh : public Component {
		private:
			GLuint VBO, VAO, EBO, texture1, texture2;
			void Texture(std::string path, GLuint *textureVar, bool flipVertical, bool alpha);
			std::vector<float> color;
		public:
			void render(Shader shader);
			Mesh(std::vector<float> v, std::vector<GLuint> i, Shader shader, std::string filePath);
	};
}