#pragma once
#include "Engine/Operator/GeometryOpDef.h"

class GOP_house
: public enzo::nt::GeometryOpDef
{
public:
    GOP_house(enzo::nt::OpId opId);
    virtual void cookOp(enzo::op::Context context);
    static enzo::nt::GeometryOpDef* ctor(enzo::nt::OpId opId)
    {
        return new GOP_house(opId);
    }

};
