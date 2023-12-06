#pragma once
#include "BaseObject.h"
#include "Scene.h"
class Skybox :
    public BaseObject{
private:
    Scene* mysc;
public:
    Skybox(Scene* sc);
    virtual void tick(float tickl);
    virtual ~Skybox();
};

