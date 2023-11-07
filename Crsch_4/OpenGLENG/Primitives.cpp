#define _USE_MATH_DEFINES
#include "Primitives.h"
#include <cmath>
namespace OpenGLENG{
	void OpenGLENG::genSphere(std::vector<GLuint>& outIndexes, std::vector<glm::vec3>& outVertices, std::vector<glm::vec2>& outTextures, std::vector<glm::vec3>& outNormals, float radius, int sectorCount, int stackCount) {
		outIndexes.clear();
		outNormals.clear();
		outVertices.clear();
		outTextures.clear();
		float x, y, z, xy;
		float nx, ny, nz, lengthInv = 1.0f / radius;
		float s, t;
		float sectorStep = 2.0f * M_PI / sectorCount;
		float stackStep = M_PI / stackCount;
		float sectorAngle, stackAngle;
		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = M_PI / 2 - i * stackStep;
			xy = radius * cosf(stackAngle);
			z = radius * sinf(stackAngle);
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;
				x = xy * cosf(sectorAngle);
				y = xy * sinf(sectorAngle);
				glm::vec3 vert;
				vert.x = x;
				vert.y = y;
				vert.z = z;
				outVertices.push_back(vert);
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				glm::vec3 norm;
				norm.x = nx;
				norm.y = ny;
				norm.z = nz;
				outNormals.push_back(norm);
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				glm::vec2 vt;
				vt.s = s;
				vt.t = t;
				outTextures.push_back(vt);
			}
			int k1, k2;
			for (int i = 0; i < stackCount; ++i)
			{
				k1 = i * (sectorCount + 1);
				k2 = k1 + sectorCount + 1;
				for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
				{
					if (i != 0)
					{
						outIndexes.push_back(k1);
						outIndexes.push_back(k2);
						outIndexes.push_back(k1 + 1);
						outIndexes.push_back(k2 + 1);
					}
				}
			}
		}
	}
	void genTorus(std::vector<GLuint>&outIndexes,std::vector<glm::vec3>&outVertices,std::vector<glm::vec2>&outTextures,std::vector<glm::vec3>&outNormals,float outerRadius,float tubeRadius, int sectorCount, int stackCount){
		outIndexes.clear();
		outNormals.clear();
		outVertices.clear();
		outTextures.clear();
		float du = 2 * M_PI / stackCount;
		float dv = 2 * M_PI / sectorCount;
		for (size_t i = 0; i < stackCount; i++) {
			float u = i * du;
			for (size_t j = 0; j <= sectorCount; j++) {
				float v = (j % sectorCount) * dv;
				for (size_t k = 0; k < 2; k++)
				{
					float uu = u + k * du;
					float x = (outerRadius + tubeRadius * cos(v)) * cos(uu);
					float y = (outerRadius + tubeRadius * cos(v)) * sin(uu);
					float z = tubeRadius * sin(v);
					outVertices.push_back(glm::vec3(x, y, z));
					float nx = cos(v) * cos(uu);
					float ny = cos(v) * sin(uu);
					float nz = sin(v);
					outNormals.push_back(glm::vec3(nx, ny, nz));
					float tx = uu / (2 * M_PI);
					float ty = v / (2 * M_PI);
					outTextures.push_back(glm::vec2(tx, ty));
				}
				v += dv;
			}
		}
		size_t size = outVertices.size();
		outIndexes.push_back(0);
		outIndexes.push_back(1);
		outIndexes.push_back(2);
		for (int k = 3; k < size; k++)
		{
			outIndexes.push_back(k - 2);
			outIndexes.push_back(k - 1);
			outIndexes.push_back(k);
		}
	}
}

