#include "GameController.h"
#include "SceneDefines.h"
GameController::GameController(int* WW, int* WH) {
	time = 0.9f;
	prevTime = glfwGetTime();
	prevxpos = 0;
	prevypos = 0;
	sensivity = 1.0f;
	WinWidth = WW;
	WinHeight = WH;
	scene = new Scene();
	mypl = new PlayerPlane(scene);
	BaseObject* b2 = new Skybox(scene);
	BaseObject* b3 = new Sea();
	Ship* y1 = new Yamato(0.0f, 0.0f, 90.0f,scene);
	Ship* s1 = new Shokaku (0.0f, -500.0f, 90.0f, scene);
	Ship* s2 = new Shokaku(0.0f, 500.0f, 90.0f, scene);
	for (int i = 0; i < 8; i++) {
		Ship* s3 = new Destroyer(2000.0f*cos(glm::radians(i*45.0f)), 2000 * sin(glm::radians(i * 45.0f)), 90.0f, scene);
		scene->addObject(s3);
	}
	DirLight l;
	l.ambient = { 0.9f, 0.9f, 0.9f };
	l.diffuse = { 0.0f, 0.0f, 0.0f };
	l.specular = { 0.9f, 0.9f, 0.9f };
	l.direction=  {0.0f, -1.0f, 1.0f };
	scene->setDirLight(l);
	scene->addObject(mypl);
	scene->addObject(b2);
	scene->addObject(b3);
	scene->addObject(y1);
	scene->addObject(s1);
	scene->addObject(s2);
}

void GameController::frame() {
	scene->render(*WinWidth,*WinHeight);
	scene->tick(float(glfwGetTime() - prevTime));
	prevTime = glfwGetTime();
}

void GameController::mouseProcessor(double xpos, double ypos) {
	scene->rotateCam(float((xpos - prevxpos) / (*WinWidth)/3.14f), float((ypos - prevypos) / (*WinHeight) / 3.14f));
	prevxpos = xpos;
	prevypos = ypos;
}

void GameController::keyboardProcessor(int key, int scancode, int action, int mods) {
 	
	if ((action == GLFW_PRESS)) {
		switch (key) {
		case GLFW_KEY_W:
			mypl->startPitch(PITCHPERTICK);
			break;
		case GLFW_KEY_S:
			mypl->startPitch(-PITCHPERTICK);
			break;
		case GLFW_KEY_A:
			mypl->startRoll(-ROLLPERTICK);
			break;
		case GLFW_KEY_D:
			mypl->startRoll(ROLLPERTICK);
			break;
		case GLFW_KEY_UP:
			mypl->speedUp(10.0f);
			break;
		case GLFW_KEY_DOWN:
			mypl->speedUp(-10.0f);
			break;
		case GLFW_KEY_LEFT: {
			time = time - 0.1f > 0.0f ? time - 0.1f : 0.0f;
			DirLight l;
			l.ambient = { time, time, time };
			l.diffuse = { 0.0f, 0.0f, 0.0f };
			l.specular = { time, time, time };
			l.direction = { 0.0f, -1.0f, 1.0f };
			scene->setDirLight(l);
		}
			break;
		case GLFW_KEY_RIGHT: {
			time = time + 0.1f < 0.9f ? time + 0.1f : 0.9f;
			DirLight l;
			l.ambient = { time, time, time };
			l.diffuse = { 0.0f, 0.0f, 0.0f };
			l.specular = { time, time, time };
			l.direction = { 0.0f, -1.0f, 1.0f };
			scene->setDirLight(l);
		}
			break;
		case GLFW_KEY_ESCAPE:
					break;
		case GLFW_KEY_N: {
			DirLight l;
			if (time < 0.5f) {
				time = 0.9f;
				l.ambient = { 0.9f, 0.9f, 0.9f };
				l.diffuse = { 0.0f, 0.0f, 0.0f };
				l.specular = { 1.0f, 1.0f, 1.0f };
				l.direction = { 0.0f, -1.0f, 1.0f };
			}
			else {
				time = 0.0f;
				l.ambient = { 0.03f, 0.03f, 0.03f };
				l.diffuse = { 0.0f, 0.0f, 0.0f };
				l.specular = { 0.03f, 0.03f, 0.03f };
				l.direction = { 0.0f, -1.0f, 1.0f };
			}
			scene->setDirLight(l);
		}
			break;
		case GLFW_KEY_V:
			scene->changeCam();
			break;
		default:
			break;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			mypl->startPitch(0);
			break;
		case GLFW_KEY_S:
			mypl->startPitch(0);
			break;
		case GLFW_KEY_A:
			mypl->startRoll(0);
			break;
		case GLFW_KEY_D:
			mypl->startRoll(0);
			break;
		}
	}
}

GameController::~GameController() {
	delete scene;
}
