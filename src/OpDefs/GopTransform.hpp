#pragma once
#include "Engine/Operator/GeometryOpDef.h"

class GopTransform
: public enzo::nt::GeometryOpDef
{
public:
    GopTransform(enzo::nt::OpId opId);
    virtual void cookOp(enzo::op::Context context);
    static enzo::nt::GeometryOpDef* ctor(enzo::nt::OpId opId)
    {
        return new GopTransform(opId);
    }

};
