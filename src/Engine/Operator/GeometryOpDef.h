#pragma once
#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/Context.h"
#include "Engine/Types.h"
#include <boost/config.hpp>


namespace enzo::nt
{
class NetworkManager;

class BOOST_SYMBOL_EXPORT GeometryOpDef
{
public:
    GeometryOpDef(enzo::nt::OpId opId);
    virtual void cookOp(op::Context context) = 0;
    geo::Geometry& getOutputGeo(unsigned outputIndex);
private:
    std::vector<enzo::geo::Geometry> outputGeometry_;
    unsigned int minInputs_;
    unsigned int maxInputs_;
    unsigned int maxOutputs_;

protected:
    enzo::nt::OpId opId_;
    const enzo::geo::Geometry& getInputGeoView(unsigned int inputIndex);
    bool outputRequested(unsigned int outputIndex);
    
    // TODO: std::move geometry instead of copying
    void setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry);
};

using opConstructor = GeometryOpDef* (*)(enzo::nt::OpId);

}
