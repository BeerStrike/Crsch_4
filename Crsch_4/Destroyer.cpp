#include "Destroyer.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"
#define MYSIZE 10.0f
std::vector<SubObject*>* Destroyer::myso;
std::vector<Material>* Destroyer::mymt;
int Destroyer::copyCounter = 0;

Destroyer::Destroyer(float x, float z, float ang, Scene* sc){
	myAng = glm::radians(ang);
	speed = 10.0f;
	mysc = sc;
	mypos = glm::vec3(x, WATERLEVEL, z);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSIZE, MYSIZE, MYSIZE));
	mytrf = glm::rotate(mytrf, myAng, glm::vec3(0.0f, 1.0f, 0.0f));
	if (copyCounter == 0) {
		myso = new std::vector<SubObject*>;
		mymt = new std::vector<Material>;
		LoadFromOBJ(DESTROYER_MODEL_FILE, myso, mymt);
	}
	copyCounter++;
	subObjects = myso;
	materials = mymt;
	PointLight p;
	p.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	p.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	p.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	p.position = glm::vec3(x, 5.0f * MYSIZE, z);
	p.linear = 0.03f;
	p.constant = 1.0f;
	p.quadratic = 0.00f;
	lamp = sc->addPointLight(p);
}

void Destroyer::tick(float tickl){
	mypos += glm::vec3(tickl * speed * sin(myAng), 0.0f, tickl * speed * cos(myAng));
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSIZE, MYSIZE, MYSIZE));
	mytrf = glm::rotate(mytrf, myAng, glm::vec3(0.0f, 1.0f, 0.0f));
	lamp->position=glm::vec3(mypos.x, 5.0f * MYSIZE, mypos.z);

}

Destroyer::~Destroyer(){
	copyCounter--;
	if (copyCounter == 0) {
		for (int i = 0; i < myso->size(); i++)
			delete myso->at(i);
		delete myso;
		for (int i = 0; i < mymt->size(); i++)
			if (materials->at(i).haveTexture)
				glDeleteTextures(1, &(mymt->at(i).texture));
		delete mymt;
	}
}
