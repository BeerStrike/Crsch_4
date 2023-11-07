#pragma once
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include "Object.h"
#include "LightStructs.h"
#include <vector>
namespace OpenGLENG {
	class Scene
	{
	private:
		glm::vec3 cameraPos;
		GLfloat cameraYaw;
		GLfloat cameraPitch;
		std::vector<Object*> objects;
		std::vector<glm::mat4> objectTrf;
		GLuint vs;
		GLuint fs;
		GLuint shader_programme;
		GLfloat fov;
		GLfloat bfc;
		GLfloat bhc;
	public:
		LightsInfo lights;

		Scene();
		void draw(int WinWidth,int WinHeight);
		void moveCam(glm::vec3 mv);
		void rotateCam(GLfloat yaw,GLfloat pitch);
		~Scene();
	};
}

