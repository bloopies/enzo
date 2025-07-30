#pragma once
#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/Context.h"
#include "Engine/Types.h"
#include <boost/config.hpp>
#include "Engine/Operator/OpInfo.h"


// forward declaration
namespace enzo::nt {class NetworkManager;}

namespace enzo::nt
{
class NetworkManager;

class BOOST_SYMBOL_EXPORT GeometryOpDef
{
public:
    GeometryOpDef(nt::NetworkManager* network, op::OpInfo opInfo);
    virtual void cookOp(op::Context context) = 0;
    geo::Geometry& getOutputGeo(unsigned outputIndex);

    unsigned int getMinInputs() const;
    unsigned int getMaxInputs() const;
    unsigned int getMaxOutputs() const;
private:
    std::vector<enzo::geo::Geometry> outputGeometry_;

protected:
    const op::OpInfo opInfo_;
    nt::NetworkManager* network_;
    bool outputRequested(unsigned int outputIndex);
    
    // TODO: std::move geometry instead of copying
    void setOutputGeometry(unsigned int outputIndex, enzo::geo::Geometry geometry);
};

using opConstructor = GeometryOpDef* (*)(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo);

}
