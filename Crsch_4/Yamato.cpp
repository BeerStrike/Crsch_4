#include "Yamato.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"
#define MYSIZE 10.0f
std::vector<SubObject*>* Yamato::myso;
std::vector<Material>* Yamato::mymt;
int Yamato::copyCounter = 0;

Yamato::Yamato(float x, float z, float ang,Scene * sc){
	myAng = glm::radians(ang);
	speed = 10.0f;
	mysc = sc;
	mypos = glm::vec3(x, WATERLEVEL,z);
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSIZE, MYSIZE, MYSIZE));
	mytrf = glm::rotate(mytrf, myAng, glm::vec3(0.0f, 1.0f, 0.0f));
	if (copyCounter == 0) {
		myso = new std::vector<SubObject*>;
		mymt = new std::vector<Material>;
		LoadFromOBJ(YAMATO_MODEL_FILE, myso, mymt);
	}
	copyCounter++;
	subObjects = myso;
	materials = mymt;
	PointLight p;
	p.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	p.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	p.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	p.position = glm::vec3(x+85.0f* MYSIZE *sin(myAng), 5.0f*MYSIZE, z+85.0f* MYSIZE *cos(myAng));
	p.linear = 0.03f;
	p.constant = 1.0f;
	p.quadratic = 0.00f;
	lamps[0] = sc->addPointLight(p);
	p.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	p.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	p.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	p.position = glm::vec3(x , 20.0f * MYSIZE, z);
	p.linear = 0.03f;
	p.constant = 1.0f;
	p.quadratic = 0.00f;
	lamps[1] = sc->addPointLight(p);

	p.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	p.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	p.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	p.position = glm::vec3(x -80.0f * MYSIZE * sin(myAng), 12.0f * MYSIZE, z -80.0f * MYSIZE * cos(myAng));
	p.linear = 0.03f;
	p.constant = 1.0f;
	p.quadratic = 0.00f;
	lamps[2] = sc->addPointLight(p);
	myGun = new YGun(glm::vec3(x - 80.0f * MYSIZE * sin(myAng), 12.0f * MYSIZE, z - 80.0f * MYSIZE * cos(myAng)),myAng);
	sc->addObject(myGun);
}

void Yamato::tick(float tickl){
	mypos += glm::vec3(  tickl * speed * sin(myAng), 0.0f, tickl * speed * cos(myAng));
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSIZE, MYSIZE, MYSIZE));
	mytrf = glm::rotate(mytrf, myAng, glm::vec3(0.0f, 1.0f, 0.0f));
	lamps[0]->position = glm::vec3(mypos.x + 85.0f * MYSIZE * sin(myAng), 5.0f * MYSIZE, mypos.z + 85.0f * MYSIZE * cos(myAng));
	lamps[1]->position = glm::vec3(mypos.x, 20.0f * MYSIZE, mypos.z);
	lamps[2]->position=glm::vec3(mypos.x - 80.0f * MYSIZE * sin(myAng), 12.0f * MYSIZE, mypos.z - 80.0f * MYSIZE * cos(myAng));
	myGun->setpos(glm::vec3(mypos.x + 35.5f * MYSIZE * sin(myAng),-4.5f * MYSIZE, mypos.z + 35.5f * MYSIZE * cos(myAng)),myAng);
}

Yamato::~Yamato(){
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
