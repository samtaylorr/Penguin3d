#include "Exceptions.h"
#include <iostream>
using namespace p3d;
using namespace std;

struct FailedGLADException {
public:
	const char* what() {
		return "Failed to initialize GLAD";
	}
};

struct FailedGLFWException {
public:
	const char* what() {
		return "Failed to create GLFW window";
	}
};