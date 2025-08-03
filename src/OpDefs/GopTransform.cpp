#include "OpDefs/GopTransform.hpp"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Parameter/Template.h"
#include "Engine/Types.h"
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/Geometry/AngleAxis.h>
#include <Eigen/src/Geometry/Transform.h>
#include <cstddef>
#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/parallel_for.h>

GopTransform::GopTransform(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo)
: GeometryOpDef(network, opInfo)
{

}

void GopTransform::cookOp(enzo::op::Context context)
{
    using namespace enzo;

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = context.cloneInputGeo(0);
        // geo::Geometry geo;

        auto PAttr = geo.getAttribByName(ga::AttrOwner::POINT, "P");
        ga::AttributeHandleVector3 PAttrHandle(PAttr);

        Eigen::Affine3d transform = Eigen::Affine3d::Identity();
        transform.rotate(Eigen::AngleAxisd(context.evalFloatParm("rotateX"), Eigen::Vector3d(1,0,0)));
        transform.rotate(Eigen::AngleAxisd(context.evalFloatParm("rotateY"), Eigen::Vector3d(0,1,0)));
        transform.rotate(Eigen::AngleAxisd(context.evalFloatParm("rotateZ"), Eigen::Vector3d(0,0,1)));
        transform.translate(bt::Vector3(context.evalFloatParm("translateX"), context.evalFloatParm("translateY"), context.evalFloatParm("translateZ")));

        const Eigen::Matrix3d  R = transform.linear();
        const Eigen::Vector3d  t = transform.translation();

        const size_t N = PAttrHandle.getSize();


        tbb::parallel_for(tbb::blocked_range<size_t>(0, N), [&](tbb::blocked_range<size_t> range)
        {
            for(size_t i=range.begin(); i<range.end(); ++i)
            {
                enzo::bt::Vector3 pointPos = PAttrHandle.getValue(i);
                pointPos = R * pointPos + t;
                // pointPos = transform*pointPos;
                PAttrHandle.setValue(i, pointPos);
            }
        });


        // set output geometry
        setOutputGeometry(0, geo);
    }

}

enzo::prm::Template GopTransform::parameterList[] = 
{
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateX", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateY", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "translateZ", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "rotateX", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "rotateY", 0),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "rotateZ", 0),
    enzo::prm::Terminator
};

