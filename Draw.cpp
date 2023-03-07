#pragma once
#include "Draw.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include "Shader.h"
#include "stb_image.h"

p3d::Polygon::Polygon(std::vector<float> v, std::vector<GLuint> i, Shader shader, std::string filePath) {
	this->color = color;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// set the GL vertex array to our defined vertex array
	glBindVertexArray(VAO);
	
	// Set our vertex buffer object to a GL type ARRAY BUFFER, 
	// and set the overall size to our array, and individual size to one float
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v.size() * 3 * sizeof(float), &v[0], GL_STATIC_DRAW);
	
	// Do the same but for our element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * 3 * sizeof(float), &i[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture creation
	this->Texture("./textures/wall.jpg", &texture1, false, false);
	this->Texture("./textures/penguin3d_graffiti.png", &texture2, true, true);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	shader.use(); // don't forget to activate/use the shader before setting uniforms!
	// either set it manually like so:
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);
}

void p3d::Polygon::Texture(std::string path, GLuint *textureVar, bool flipVertical, bool alpha)
{
	int width, height, nrChannels;

	glGenTextures(1, textureVar);
	glBindTexture(GL_TEXTURE_2D, *textureVar);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (flipVertical) {
		stbi_set_flip_vertically_on_load(false);
	}
	else {
		stbi_set_flip_vertically_on_load(true);
	}

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alpha) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void p3d::Polygon::render(Shader shader) {
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	shader.use();
	// Bind the GL vertex array to our created array
	glBindVertexArray(VAO);
	// Draw triangles based on our vertex and element buffer objects
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}