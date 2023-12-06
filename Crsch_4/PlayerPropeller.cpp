#include "PlayerPropeller.h"
#include "ModelFilesDefines.h"
#include "SceneDefines.h"

std::vector<SubObject*>* PlayerPropeller::myso;
std::vector<Material>* PlayerPropeller::mymt;
int PlayerPropeller::copyCounter = 0;



PlayerPropeller::PlayerPropeller(glm::vec3 pos){
	ang = 0.0f;
	rtspeed = 60.0f;
	subObjects = new std::vector<SubObject*>;
	materials = new std::vector<Material>;
	mytrf = glm::mat4(1.0f);
	mytrf = glm::translate(mytrf, mypos);
	if (copyCounter == 0) {
		myso = new std::vector<SubObject*>;
		mymt = new std::vector<Material>;
		LoadFromOBJ(PLAYERPROPELLER_MODEL_FILE, myso, mymt);
	}
	copyCounter++;
	subObjects = myso;
	materials = mymt;
}

void PlayerPropeller::tick(float tickl){
	ang += rtspeed * tickl;
	if (ang > 6.28)
		ang = 0;
}

void PlayerPropeller::setTrf(glm::mat4 trf){
	mytrf = trf;
	mytrf = glm::rotate(mytrf, ang, { 0.0f,0.0f,1.0f });
}

void PlayerPropeller::RtSpeedUp(float spd){
	rtspeed += spd;
}

PlayerPropeller::~PlayerPropeller(){
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
