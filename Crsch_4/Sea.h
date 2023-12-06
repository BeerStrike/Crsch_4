#pragma once
#include "BaseObject.h"
class Sea :
    public BaseObject{
public:
    Sea();
    virtual void tick(float tickl);
    virtual ~Sea();
};

