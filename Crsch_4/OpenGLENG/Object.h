#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include "LightStructs.h"
#include <vector>
namespace OpenGLENG {
	class Object {
	private:
		GLuint coords_vbo;
		GLuint normals_vbo;
		GLuint tex_vbo;
		GLuint vao;
		GLuint pointn;
		GLuint elementbuffer;
		Material material;
	public:
		Object(std::vector<GLuint> indices,std::vector<glm::vec3>& points, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals, Material mtr,std::string textureFile, std::string specularMapFile);
		static Object* LoadFromOBJ(std::string filename);
		void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, LightsInfo lights, glm::vec3 campos, GLuint shader_programme);
		~Object();
	};
}

