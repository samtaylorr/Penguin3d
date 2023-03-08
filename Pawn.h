#pragma once
#include "Component.h"
#include <vector>

namespace p3d {
    class Pawn {
    public:
        void AddComponent(Component component)
        {
            components.push_back(component);
        }
    private:
        std::vector<Component> components;
    };
}