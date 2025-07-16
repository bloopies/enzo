#include "OpDefs/GopTransform.hpp"
#include "Engine/Operator/AttributeHandle.h"

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

