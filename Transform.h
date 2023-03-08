#pragma once
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace p3d {
	typedef glm::vec3 Vector3;
	typedef glm::vec2 Vector2;
	typedef glm::mat4 Matrix4;

	class Transform
	{
	private:
		Shader* shader;
		Vector3* position;
	public:
		Transform(Shader* s);
		void Translate(Vector3* vector);
		void sendToShader(Matrix4 matrix);
	}; 
}