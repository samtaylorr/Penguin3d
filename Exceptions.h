#pragma once
#include <iostream>

namespace p3d {
    struct FailedGLADException :
        public std::exception
    {
    public:
        char* what();
    };

    struct FailedGLFWException :
        public std::exception
    {
    public:
        char* what();
    };
}