#pragma once
#include "Engine/Operator/GeometryOpDef.h"
#include "Engine/Parameter/Template.h"

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

    static BOOST_SYMBOL_EXPORT enzo::prm::Template parameterList[];

};
