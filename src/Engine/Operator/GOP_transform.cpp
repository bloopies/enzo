#include "Engine/Operator/GOP_transform.h"
#include "Engine/Operator/AttributeHandle.h"
#include <oneapi/tbb/parallel_for.h>

GOP_transform::GOP_transform(enzo::nt::OpId opId)
: enzo::nt::GeometryOpDef(opId)
{

}

void GOP_transform::cookOp()
{
    using namespace enzo;
    // std::cout << "COOKING\n";

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = cloneInputGeo(0);

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

