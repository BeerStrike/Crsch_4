#include "MainGameClass.h"

 OpenGLENG::Scene* MainGameClass::s;
 int MainGameClass::WinWidth;
 int MainGameClass::WinHeight;

void MainGameClass::keyProcessor(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    else  if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        s->moveCam({ 0.1f,0.0f,0.0f });
    else  if (key == GLFW_KEY_D && action == GLFW_REPEAT)
        s->moveCam({ -0.1f,0.0f,0.0f });
    else  if (key == GLFW_KEY_W && action == GLFW_REPEAT)
        s->moveCam({ 0.0f,0.0f,0.1f });
    else  if (key == GLFW_KEY_S && action == GLFW_REPEAT)
        s->moveCam({ 0.0f,0.0f,-0.1f });
    else  if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        s->rotateCam(-0.03f, 0.0f);
    else  if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        s->rotateCam(0.03f, 0.0f);
    else  if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        s->rotateCam(0.0f, 0.03f);
    else  if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        s->rotateCam(0.0f, -0.03f);
}


void MainGameClass::startGame(int WW,int WH){
    WinWidth = WW;
    WinHeight = WH;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Crsch_4",
        NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetWindowSizeCallback(window,glfw_window_size_callback);
    glfwSetKeyCallback(window, keyProcessor);
    s = new OpenGLENG::Scene();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glViewport(0, 0, WinWidth, WinHeight);
        s->draw(WinWidth, WinHeight);
        glfwSwapBuffers(window);
    }
    delete s;
    glfwTerminate();
}

void MainGameClass::glfw_window_size_callback(GLFWwindow* window, int width, int height) {
        WinWidth = width;
        WinHeight = height;
}