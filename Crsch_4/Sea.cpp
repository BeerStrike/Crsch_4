#include "Sea.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"
Sea::Sea()
{
	mypos = glm::vec3(0.0f, 0.0f, 0.0f);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, { 0.0f,WATERLEVEL,0.0f });
	mytrf = glm::scale(mytrf, { MAPSIZE,1.0f,MAPSIZE });
	LoadFromOBJ(SEA_MODEL_FILE, subObjects, materials);
}

void Sea::tick(float tickl)
{
}

Sea::~Sea()
{
	for (int i = 0; i < subObjects->size(); i++)
		delete subObjects->at(i);
	delete subObjects;
	for (int i = 0; i < materials->size(); i++)
		if (materials->at(i).haveTexture)
			glDeleteTextures(1, &(materials->at(i).texture));
	delete materials;
}
