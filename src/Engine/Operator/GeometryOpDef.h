#pragma once
#include "Engine/Operator/Geometry.h"
#include "Engine/Types.h"

namespace enzo::nt
{
class GeometryOpDef
{
public:
    GeometryOpDef(enzo::nt::OpId opId);
    virtual void cookOp() = 0;
    geo::Geometry& getOutputGeo(unsigned outputIndex);
private:
    std::vector<enzo::geo::Geometry> outputGeometry_;
    unsigned int minInputs_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;
protected:
    enzo::nt::OpId opId_;
    const enzo::geo::Geometry& getInputGeoView(unsigned int inputIndex);
    enzo::geo::Geometry cloneInputGeo(unsigned int inputIndex);
    bool outputRequested(unsigned int outputIndex);
    
    // TODO: std::move geometry instead of copying
    void setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry);
};
}
