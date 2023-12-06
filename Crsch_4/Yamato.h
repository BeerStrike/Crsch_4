#pragma once
#include "Ship.h"
#include "LightStructs.h"
#include "Scene.h"
#include "YGun.h"
class Yamato :
    public Ship {
private:
    static std::vector<SubObject*>* myso;
    static std::vector<Material>* mymt;
    static int copyCounter;
    PointLight *lamps[3];
    Scene* mysc;
    YGun* myGun;
public:
    Yamato(float x,float z,float ang,Scene* s);
    virtual void tick(float tickl);
    virtual ~Yamato();
};

