#include "OpDefs/GopTransform.hpp"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Parameter/Template.h"

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
            vector.x()+=context.evalFloatParm("translateX");
            vector.y()+=context.evalFloatParm("translateY");
            vector.z()+=context.evalFloatParm("translateZ");
            PAttrHandle.setValue(i, vector);
        }
        // ----



        // set output geometry
        setOutputGeometry(0, geo);
    }

}

enzo::prm::Template GopTransform::parameterList[] = 
{
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateX", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateY", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateZ", 0),
    enzo::prm::Terminator
};

