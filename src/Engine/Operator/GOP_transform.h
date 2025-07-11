#pragma once
#include "Engine/Operator/GeometryOpDef.h"

class GOP_transform
: public enzo::nt::GeometryOpDef
{
public:
    GOP_transform(enzo::nt::OpId opId);
    virtual void cookOp();
    static enzo::nt::GeometryOpDef* ctor(enzo::nt::OpId opId)
    {
        return new GOP_transform(opId);
    }

};
