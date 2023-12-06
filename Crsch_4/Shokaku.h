#pragma once
#include "Ship.h"
#include "Scene.h"
class Shokaku :
    public Ship{
private:
    static std::vector<SubObject*>* myso;
    static std::vector<Material>* mymt;
    static int copyCounter;
    PointLight* lamps[2];
    Scene* mysc;
public:
    Shokaku(float x, float z, float ang, Scene* s);
    virtual void tick(float tickl);
    virtual ~Shokaku();
};

