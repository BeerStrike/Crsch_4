#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include <string>
#include <vector>
#include "SubObject.h"
#include "tiny_obj_loader.h"
#include "stb_image.h"

class BaseObject {
	private:
	
	protected:
		std::vector<SubObject*>* subObjects;
		std::vector<Material>* materials;
		glm::mat4 mytrf;
		glm::vec3 mypos;
	public:
		static void LoadFromOBJ(std::string filename, std::vector<SubObject*>* so, std::vector<Material>* ms);
		void draw(glm::mat4 projection, glm::mat4 view, glm::vec3 campos, LightsInfo lights, GLuint shader_programme);
		virtual void tick(float tickl)=0;
		glm::vec3 getPos();
		virtual ~BaseObject();
};

