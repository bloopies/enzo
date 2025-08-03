#pragma once

#include "Engine/Types.h"
#include "Engine/Operator/Geometry.h"

namespace enzo::nt
{
    class NetworkManager;
}

namespace enzo::op
{
class Context
{
public:
    Context(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager);
    enzo::geo::Geometry cloneInputGeo(unsigned int inputIndex);
    bt::floatT evalFloatParm(const char* parmName, const unsigned int index=0) const;
private:
    enzo::nt::OpId opId_;
    enzo::nt::NetworkManager& networkManager_;

};
}
