#pragma once
#include "BaseObject.h"
class YGun :
    public BaseObject {
private:
    static std::vector<SubObject*>* myso;
    static std::vector<Material>* mymt;
    static int copyCounter;
    float ang;
    float shipAng;
    bool rtl;
public:
    YGun(glm::vec3 pos, float shpAng);
    virtual void tick(float tickl);
    void setpos(glm::vec3 pos, float shpAng);
    virtual ~YGun();
};

