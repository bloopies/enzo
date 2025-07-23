#pragma once
#include <string>
#include "Engine/Operator/GeometryOpDef.h"
#include "Engine/Parameter/Template.h"

namespace enzo::op
{
struct OpInfo
{
    std::string internalName;
    std::string displayName;
    enzo::nt::opConstructor ctorFunc;
    enzo::prm::Template* templates;
    size_t templatesSize;
};
}
