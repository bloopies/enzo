#pragma once
#include "Engine/Operator/Geometry.h"

namespace enzo::nt
{
class GeometryOpDef
{
public:
    GeometryOpDef();
    void cookOp();
    geo::Geometry& getOutputGeo(unsigned outputIndex);
private:
    std::vector<enzo::geo::Geometry> outputGeometry_;
    unsigned int minInputs_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;
protected:
    const enzo::geo::Geometry& getInputGeoView(unsigned int inputIndex);
    enzo::geo::Geometry cloneInputGeo(unsigned int inputIndex);
    bool outputRequested(unsigned int outputIndex);
    
    void setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry);
};
}
