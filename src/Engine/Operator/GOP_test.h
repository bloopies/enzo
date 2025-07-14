#pragma once
#include "Engine/Operator/GeometryOpDef.h"

class GOP_test
: public enzo::nt::GeometryOpDef
{
public:
    GOP_test(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager);
    virtual void cookOp();
    static enzo::nt::GeometryOpDef* ctor(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager)
    {
        return new GOP_test(opId, networkManager);
    }

};
