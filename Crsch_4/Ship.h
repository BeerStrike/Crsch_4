#pragma once
#include "BaseObject.h"
class Ship :
    public BaseObject {
protected:
    float myAng;
    float speed;
public:
    virtual ~Ship();
};

