#pragma once
#include "Ship.h"
#include "LightStructs.h"
#include "Scene.h"
class Destroyer :
    public Ship{
private:
    static std::vector<SubObject*>* myso;
    static std::vector<Material>* mymt;
    static int copyCounter;
    PointLight* lamp;
    Scene* mysc;

public:
    Destroyer(float x, float z, float ang, Scene* s);
    virtual void tick(float tickl);
    virtual ~Destroyer();
};