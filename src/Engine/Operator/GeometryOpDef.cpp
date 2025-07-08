#include "Engine/Operator/GeometryOpDef.h"
#include <stdexcept>
#include <iostream>

bool enzo::nt::GeometryOpDef::outputRequested(unsigned int outputIndex)
{
    // TODO: implement
    return true;
}

const enzo::geo::Geometry& enzo::nt::GeometryOpDef::getInputGeoView(unsigned int inputIndex)
{
    // TODO: implement
    return enzo::geo::Geometry();

}

enzo::geo::Geometry enzo::nt::GeometryOpDef::cloneInputGeo(unsigned int inputIndex)
{
    // TODO: implement
    return enzo::geo::Geometry();
}

void enzo::nt::GeometryOpDef::setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry)
{
    if(outputIndex>maxOutputs_)
    {
        throw std::runtime_error("Cannot set output geometry to index > maxOutputs");
    }
    outputGeometry_[outputIndex] = geometry;
}

enzo::nt::GeometryOpDef::GeometryOpDef()
{
    minInputs_=1;
    maxInputs_=4;
    maxOutputs_=4;
    outputGeometry_ = std::vector<enzo::geo::Geometry>(4, enzo::geo::Geometry());
}

void enzo::nt::GeometryOpDef::cookOp()
{
    using namespace enzo;
    std::cout << "COOKING\n";

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = cloneInputGeo(0);

        // set output geometry
        setOutputGeometry(0, geo);
    }

    // if(outputRequested(1))
    // {
    //     // create new geometry
    //     const geo::Geometry& geo1 = getInputGeoView(0);
    //     geo::Geometry geo2;

    //     setOutputGeometry(1, geo2);
    // }
}
