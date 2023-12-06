#pragma once
#include "BaseObject.h"
#include "Scene.h"
#include "ModelFilesDefines.h"
#include "LightStructs.h"
#include "PlayerPropeller.h"
class PlayerPlane :
    public BaseObject{
    private:
       static std::vector<SubObject*>* myso;
       static std::vector<Material>* mymt;
       static int copyCounter;
       float speed;
       float rtspeed;
       float myroll, mypitch,myyaw;
       Scene* mysc;
        float ppt;
        float rpt;
        PointLight* cabLight;
        SpotLight* frwLamp;
        PlayerPropeller* pr;
    public:
        PlayerPlane(Scene* sc);
        void startRoll(float proll);
        void startPitch(float ppitch);
        virtual void tick(float tickl);
        void speedUp(float add);
         virtual ~PlayerPlane();
};

