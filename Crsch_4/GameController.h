#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include "Scene.h"

#include "BaseObject.h"
#include "PlayerPlane.h"
#include "Skybox.h"
#include "Sea.h"
#include "Yamato.h"
#include "Shokaku.h"
#include "Destroyer.h"
class GameController {
	private:
		double prevTime;
		double prevxpos;
		double prevypos;
		float sensivity;
		int *WinWidth;
		int *WinHeight;
		Scene* scene;
		PlayerPlane *mypl;
		float time;
	public:
		GameController(int *WW,int *WH);
		void frame();
		void mouseProcessor(double xpos,double ypos);
		void keyboardProcessor(int key, int scancode, int action, int mods);
		~GameController();
};

