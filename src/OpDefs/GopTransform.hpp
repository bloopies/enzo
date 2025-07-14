#pragma once
#include "Engine/Operator/GeometryOpDef.h"

class GopTransform
: public enzo::nt::GeometryOpDef
{
public:
    GopTransform(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager);
    virtual void cookOp();
    static enzo::nt::GeometryOpDef* ctor(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager)
    {
        return new GopTransform(opId, networkManager);
    }

};
