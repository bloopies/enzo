#include "Engine/Operator/OperatorTable.h"
#include "OpDefs/GopTransform.hpp"
#include <boost/config.hpp>
#include <boost/dll.hpp>
#include <string>
#include "Engine/Operator/AttributeHandle.h"
#include <iostream>

extern "C"
{
    BOOST_SYMBOL_EXPORT void newSopOperator(enzo::op::addOperatorPtr addOperator)
    {
        addOperator(
            "transform",
            "Transform",
            &GopTransform::ctor
        );
    }

}

GopTransform::GopTransform(enzo::nt::OpId opId)
: enzo::nt::GeometryOpDef(opId)
{

}

void GopTransform::cookOp(enzo::op::Context context)
{
    using namespace enzo;

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = context.cloneInputGeo(0);

        // ----
        // create geometry start
        // ----
        auto PAttr = geo.getAttribByName(ga::AttrOwner::POINT, "P");
        ga::AttributeHandleVector3 PAttrHandle(PAttr);

        for(int i=0; i<PAttrHandle.getAllValues().size(); ++i)
        {
            enzo::bt::Vector3 vector = PAttrHandle.getValue(i);
            vector.y()+=2.5;
            PAttrHandle.setValue(i, vector);
        }
        // ----



        // set output geometry
        setOutputGeometry(0, geo);
    }

}

