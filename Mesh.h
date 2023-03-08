#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"

namespace p3d {
	class Mesh {
		private:
			GLuint VBO, VAO, EBO, texture1, texture2;
			void Texture(std::string path, GLuint *textureVar, bool flipVertical, bool alpha);
			std::vector<float> color;
			Shader* shader;
		public:
			void render();
			Mesh(std::vector<float> v, std::vector<GLuint> i, Shader* shader, std::string filePath);
			Shader* getShader();
			void setShader(Shader* shader);
	};
}