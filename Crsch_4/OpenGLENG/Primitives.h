#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <glm.hpp>
#include <vector>
namespace OpenGLENG{
	void genTorus(std::vector<GLuint>& outIndexes, std::vector < glm::vec3 >& outVertices, std::vector < glm::vec2 >& outTextures, std::vector < glm::vec3 >& outNormals, float outerRadius, float tubeRadius, int sectorCount, int stackCount);
	void genSphere(std::vector<GLuint>& outIndexes, std::vector < glm::vec3 >& outVertices, std::vector < glm::vec2 >& outTextures, std::vector < glm::vec3 >& outNormals, float radius, int sectorCount, int stackCount);
} 