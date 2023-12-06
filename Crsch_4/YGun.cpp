#include "YGun.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"
#define MYSCALE 10.0f
std::vector<SubObject*>* YGun::myso;
std::vector<Material>* YGun::mymt;
int YGun::copyCounter = 0;

YGun::YGun(glm::vec3 pos, float shpAng){
	shipAng = shpAng;
	rtl = true;
	ang = 0.0f;
	mypos = pos;
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSCALE, MYSCALE, MYSCALE));
	if (copyCounter == 0) {
		myso = new std::vector<SubObject*>;
		mymt = new std::vector<Material>;
		LoadFromOBJ(YAMATO_GUN_MODEL_FILE, myso, mymt);
	}
	copyCounter++;
	subObjects = myso;
	materials = mymt;
}

void YGun::tick(float tickl){
	ang = ang + tickl * 10.0f *( rtl ? -1 : 1);
	if (ang >= 90.0f) {
		rtl = !rtl;
		ang = 90.0f;
	}
	if (ang <= -90.0f) {
		rtl = !rtl;
		ang = -90.0f;
	}
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::scale(mytrf, glm::vec3(MYSCALE, MYSCALE, MYSCALE));
	mytrf = glm::rotate(mytrf,glm::radians(ang) + shipAng, glm::vec3(0.0f, 1.0f, 0.0f));
}

void YGun::setpos(glm::vec3 pos,float shpAng){
	mypos = pos;
	shipAng = shpAng;
}

YGun::~YGun(){
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
