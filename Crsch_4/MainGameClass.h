#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include "OpenGLENG/Scene.h"

class MainGameClass{
private:
	static OpenGLENG::Scene* s;
	static int WinWidth;
	static int WinHeight;
public:
	static void keyProcessor(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void startGame(int WW, int WH);
	static void glfw_window_size_callback(GLFWwindow* window, int width, int height);
};

