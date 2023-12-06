#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include "GameController.h"
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);

int WinWidth = 640;
int WinHeight = 480;
GameController* gc;
int main() {

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Crsch_4",
        NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, keyboard_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    gc = new GameController(&WinWidth,&WinHeight);
    glEnable(GL_DEPTH_TEST);  
    glDepthFunc(GL_LESS);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gc->frame();
        glfwSwapBuffers(window);
    }
    delete gc;
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    gc->mouseProcessor(xpos,ypos);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    gc->keyboardProcessor(key, scancode, action, mods);
}


void window_size_callback(GLFWwindow* window, int width, int height) {
    WinWidth = width;
    WinHeight = height;
}