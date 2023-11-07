#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include <iostream> 
#include "OpenGLENG/ShaderFuncs.h"
#include "OpenGLENG/Scene.h"
#include <cmath>
int WinWidth = 640;
int WinHeight = 480;

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int chse;
GLfloat dist;
GLfloat ang;
GLfloat mv;
GLfloat rt;
OpenGLENG::Scene *s;

int main() {
    dist = 8.0f;
    ang = 0.0f;
    mv = 0.0f;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "PR7",
        NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    chse = 0;
    s = new OpenGLENG::Scene();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glViewport(0, 0, WinWidth, WinHeight);
        s->draw(WinWidth,WinHeight);
        glfwSwapBuffers(window);
    }
    delete s;
    glfwTerminate();
    return 0;
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    WinWidth = width;
    WinHeight = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    else  if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        s->moveCam({ 0.1f,0.0f,0.0f });
    else  if (key == GLFW_KEY_D && action == GLFW_REPEAT)
        s->moveCam({-0.1f,0.0f,0.0f });
    else  if (key == GLFW_KEY_W && action == GLFW_REPEAT)
        s->moveCam({ 0.0f,0.0f,0.1f });
    else  if (key == GLFW_KEY_S && action == GLFW_REPEAT)
        s->moveCam({ 0.0f,0.0f,-0.1f });
    else  if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        s->rotateCam(-0.03f,0.0f);
    else  if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        s->rotateCam(0.03f, 0.0f);
    else  if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        s->rotateCam(0.0f, 0.03f);
    else  if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        s->rotateCam(0.0f, -0.03f);
    else  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (s->lights.dirLight.specular.r == 0.0f)
            s->lights.dirLight.specular = { 0.5f,0.5f,0.5f };
        else
            s->lights.dirLight.specular = { 0.0f,0.0f,0.0f };
    }

} 