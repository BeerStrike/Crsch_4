#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include <vector>
#include "ShaderFuncs.h"
#include "LightStructs.h"
#include "BaseObject.h"
#include "Scene.h"
class Scene {
	private:
		LightsInfo lights;
		std::vector<BaseObject*> Objects;
		GLuint vs;
		GLuint fs;
		GLuint shader_programme;
		glm::vec3 campos;
		glm::vec3 camdir;
		float cameraYaw;
		float cameraPitch;
		bool camType;
		float camDist;
	public:
		Scene();
		void addObject(BaseObject *obj);
		void render(int WW,int WH);
		void tick(float tickl);
		void setCampos(glm::vec3 newpos);
		glm::vec3 getCampos();
		void moveCam(glm::vec3 mv);
		void rotateCam(float yaw,float pitch);
		void changeCam();
		void setDirLight(DirLight l);
		PointLight* addPointLight(PointLight p);
		SpotLight* addSpotLight(SpotLight s);
		~Scene();
};

