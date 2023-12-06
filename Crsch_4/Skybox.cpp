#include "Skybox.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"
Skybox::Skybox(Scene * sc)
{
	mysc = sc;
	mypos = glm::vec3(0.0f, 0.0f, 0.0f);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::scale(mytrf, { SKYBOXSIZE,SKYBOXSIZE,SKYBOXSIZE });
	LoadFromOBJ(SKYBOX_MODEL_FILE, subObjects, materials);
}

void Skybox::tick(float tickl)
{
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mysc->getCampos());
	mytrf = glm::scale(mytrf, { SKYBOXSIZE,SKYBOXSIZE,SKYBOXSIZE });
	mypos = mysc->getCampos();
}

Skybox::~Skybox()
{
	for (int i = 0; i < subObjects->size(); i++)
		delete subObjects->at(i);
	delete subObjects;
	for (int i = 0; i < materials->size(); i++)
		if(materials->at(i).haveTexture)
			glDeleteTextures(1, &(materials->at(i).texture));
	delete materials;
}
