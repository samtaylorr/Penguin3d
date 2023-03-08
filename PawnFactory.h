#pragma once
#include "Pawn.h"
#include "Mesh.h"

namespace p3d {
	class PawnFactory
	{
	private:
		Shader* shader;
		Mesh* mesh;
	public:
		Pawn* CreatePawn();
	};
}