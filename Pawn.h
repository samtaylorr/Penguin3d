#pragma once
#include <vector>
#include "Mesh.h"
#include "Transform.h"

struct Components {
    p3d::Mesh *mesh;
    p3d::Transform *transform;
};

namespace p3d {
    class Pawn {
    public:
        Pawn() = default;
        Components components;

        void AddMesh(Mesh* mesh)
        {
            components.mesh = mesh;
        }

        Mesh* GetMesh() {
            return components.mesh;
        }

        void AddTransform(Transform* t)
        {
            components.transform = t;
        }

        Transform* GetTransform() {
            return components.transform;
        }
    };
}