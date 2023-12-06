#pragma once
#include "BaseObject.h"
class PlayerPropeller :
    public BaseObject{
private:
    static std::vector<SubObject*>* myso;
    static std::vector<Material>* mymt;
    static int copyCounter;
    float ang;
    float rtspeed;
    public:
        PlayerPropeller(glm::vec3 pos);
        virtual void tick(float tickl);
        void setTrf(glm::mat4 trf);
        void RtSpeedUp(float spd);
       virtual ~PlayerPropeller();

};
