#pragma once
#include <vector>
#include <glm.hpp>
#include<gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
namespace OpenGLENG {
	bool OBJLoad(const char* filename, std::vector<glm::vec3>& points, std::vector<glm::vec2>& textures, std::vector<glm::vec3>& normals);
}