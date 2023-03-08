#include "PawnFactory.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"

using namespace p3d;

Pawn* p3d::PawnFactory::CreatePawn() {
	Pawn *pawn = new Pawn();
    Shader* shader = new Shader("vertex_shader.glsl", "fragment_shader.glsl");
    Transform* transform = new Transform(shader);

    std::vector<float>* vertices = new std::vector<float>{
        // positions           // colors             // tex_coordinates
        0.9f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,          // bottom right
       -0.9f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     0.0f, 0.0f,          // bottom left
       -0.9f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     1.0f, 0.0f,          // top left
        0.9f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f,     1.0f, 1.0f           // top right
    };

    std::vector<GLuint>* indices = new std::vector<GLuint>{
        2, 3, 0,
        0, 1, 2,
    };

    p3d::Mesh* mesh = new p3d::Mesh(*vertices, *indices, shader, "./textures/wall.jpg");
    delete vertices;
    delete indices;
	pawn->AddMesh(mesh);
    pawn->AddTransform(transform);

	return pawn;
}