#pragma once
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"
#include <variant>

namespace enzo
{
class Primitive
{
public:
    Primitive();
    bool addIntAttrib(AttributeOwner owner, AttributeInt attribute);
    AttributeInt findAttribByName(AttributeOwner owner, std::string name);
private:
    std::vector<std::variant<
        AttributeInt,
        AttributeFloat
    >> pointAttribs_;
};
}
