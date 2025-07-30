#pragma once
#include <string>
#include "Engine/Parameter/Template.h"

// forward declaration
namespace enzo::op
{
    struct OpInfo;
}
namespace enzo::nt
{
    class GeometryOpDef;
    class NetworkManager;
    using opConstructor = GeometryOpDef* (*)(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo);
}

namespace enzo::op
{
struct OpInfo
{
    std::string internalName;
    std::string displayName;
    enzo::nt::opConstructor ctorFunc;
    enzo::prm::Template* templates;
    unsigned int minInputs=0;
    unsigned int maxInputs=1;
    unsigned int maxOutputs=1;
};
}

