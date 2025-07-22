#pragma once
#include "Engine/Operator/GeometryOpDef.h"
#include "Engine/Parameter/Template.h"

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

    static BOOST_SYMBOL_EXPORT enzo::prm::Template parameterList[];

};
