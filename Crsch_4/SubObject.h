#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include "LightStructs.h"
#include <vector>
#include <string>
class SubObject {
	private:
		GLuint coords_vbo;
		GLuint normals_vbo;
		GLuint tex_vbo;
		GLuint vao;
		int vertex_num;
		Material *material;
	public:
		SubObject(std::vector<glm::vec3>* points, std::vector<glm::vec2>* textures, std::vector<glm::vec3>* normals, Material *mtr);
		void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 campos, LightsInfo lights, GLuint shader_programme);
		~SubObject();
};

