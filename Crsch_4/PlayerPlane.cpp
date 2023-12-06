#include "PlayerPlane.h"
#include "SceneDefines.h"
std::vector<SubObject*>* PlayerPlane::myso;
std::vector<Material>* PlayerPlane::mymt;
int PlayerPlane::copyCounter=0;
PlayerPlane::PlayerPlane( Scene* sc){
	myyaw = 0;
	myroll =0;	
	mypitch = 0;
	ppt = rpt = 0;
	mypos = { 0.0f,0.0f,0.0f };
	mysc = sc;
	mytrf = glm::mat4(1.0f);
	//pos = pos + glm::vec3(0.0f, -1.6f, -2.8f);
	mytrf = glm::rotate(mytrf, glm::radians(90.0f), { 0.0f,1.0f,0.0f });
	if (copyCounter == 0) {
		myso = new std::vector<SubObject*>;
		mymt = new std::vector<Material>;
		LoadFromOBJ(PLAYERPLANE_MODEL_FILE,myso, mymt);
	}
	subObjects = myso;
	materials = mymt;
	copyCounter++;
	rtspeed =1.0f;
	speed = 60.0f;
	PointLight p;
	p.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	p.diffuse= glm::vec3(1.0f, 1.0f, 1.0f);
	p.specular= glm::vec3(1.0f, 1.0f, 1.0f);
	p.position= glm::vec3(0.0f, 0.0f, 0.0f);
	p.linear = 0.09f;
	p.constant = 1.0f;
	p.quadratic = 0.03f;
	cabLight = mysc->addPointLight(p);
	SpotLight s;
	s.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
	s.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	s.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	s.position = glm::vec3(5.0f, 0.0f, 0.0f);
	s.linear = 0.01f;
	s.constant = 1.0f;
	s.quadratic = 0.00f;
	s.cutOff = 0.95f;
	s.outerCutOff = 1.0;
	s.direction= glm::vec3(7.0f, 0.0f, 0.0f);
	frwLamp = mysc->addSpotLight(s);
	pr = new PlayerPropeller({ 0.0f,0.0f,0.0f });
	sc->addObject(pr);
}

void PlayerPlane::speedUp(float add){
	if (speed + add <= 500.0f && speed + add >= 50.0f) {
		speed += add;
		pr->RtSpeedUp(add);
	}
}

void PlayerPlane::tick(float tickl)
{
	if (myroll + rpt*tickl<1 && myroll + rpt* tickl>-1) {
		myroll += rpt* tickl;
	}
	if (mypitch + ppt* tickl<1 && mypitch + ppt* tickl>-1) {
		mysc->rotateCam(0.0f, ppt* tickl);
		mypitch += ppt* tickl;
	}
	myyaw += rtspeed * myroll*tickl;
	mytrf = glm::mat4(1.0f);
	glm::vec3 mv= glm::vec3((glm::abs(mypos.x+ tickl * speed*cos(myyaw) * cos(mypitch)) <=(MAPSIZE-SKYBOXSIZE))?cos(myyaw) * cos(mypitch):0,sin(-mypitch), (glm::abs(mypos.z+ tickl * speed *sin(myyaw) * cos(mypitch)) <= (MAPSIZE - SKYBOXSIZE))?sin(myyaw) * cos(mypitch):0);
	mv *= tickl * speed;
	mypos += mv;
	mytrf = glm::translate(mytrf, mypos);
	mytrf = glm::rotate(mytrf, glm::radians(90.0f)- myyaw, { 0.0f,1.0f,0.0f });
	mytrf = glm::rotate(mytrf, mypitch, { 1.0f,0.0f,0.0f });
	mytrf = glm::rotate(mytrf, myroll, { 0.0f,0.0f,1.0f });
	mysc->moveCam(mv);
	mysc->rotateCam(rtspeed * myroll * tickl, 0.0f);
	cabLight->position = mypos;
	mv /= tickl * speed;
	mv *= 10;
	frwLamp->position =mypos+mv;
	frwLamp->direction = mv;
	if (mypos.y <= WATERLEVEL+10)
		mypitch = -0.1f;
	if (mypos.y >= MAXHIGTH)
		mypitch = 0.1f;
	pr->setTrf(glm::translate(mytrf,{0.0f,-1.5f,4.8f}));
}

PlayerPlane::~PlayerPlane(){
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

void PlayerPlane::startRoll(float proll)
{
	rpt = proll;
}

void PlayerPlane::startPitch(float ppitch)
{
	ppt = ppitch;
}
