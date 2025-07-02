#pragma once
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"
#include <variant>

namespace enzo::geo
{
class Geometry
{
public:
    Geometry();
    ga::AttributeHandle<int> addIntAttribute(ga::AttributeOwner owner, std::string name);
    ga::AttributeHandle<bt::Vector3> addVector3Attribute(ga::AttributeOwner owner, std::string name);
    std::shared_ptr<ga::Attribute> getAttribByName(ga::AttributeOwner owner, std::string name);
private:
    using attribVector = std::vector<std::shared_ptr<ga::Attribute>>;
    attribVector& getAttributeStore(ga::AttributeOwner& owner);
    attribVector pointAttributes_;
    attribVector vertexAttributes_;
    attribVector primitiveAttributes_;
    attribVector globalAttributes_;
};
}
