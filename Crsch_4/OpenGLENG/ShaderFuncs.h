#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 

namespace OpenGLENG {
	GLuint LoadShader(std::string filename, GLenum type);
}