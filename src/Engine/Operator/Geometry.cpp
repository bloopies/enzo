#include "Engine/Operator/Geometry.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include <memory>
#include <stdexcept>

using namespace enzo;
geo::Geometry::Geometry()
{
    addVector3Attribute(ga::AttrOwner::POINT, "P");
    addIntAttribute(ga::AttrOwner::VERTEX, "point");
}

ga::AttributeHandle<int> geo::Geometry::addIntAttribute(ga::AttributeOwner owner, std::string name)
{
    auto newAttribute = std::make_shared<ga::Attribute>(name, ga::AttrType::intT);
    getAttributeStore(owner).push_back(newAttribute);
    return ga::AttributeHandle<int>(newAttribute);
}

ga::AttributeHandle<bt::Vector3> geo::Geometry::addVector3Attribute(ga::AttributeOwner owner, std::string name)
{
    auto newAttribute = std::make_shared<ga::Attribute>(name, ga::AttrType::vectorT);
    getAttributeStore(owner).push_back(newAttribute);
    return ga::AttributeHandle<bt::Vector3>(newAttribute);
}

std::vector<std::shared_ptr<ga::Attribute>>& geo::Geometry::getAttributeStore(ga::AttributeOwner& owner)
{
    switch(owner)
    {
        case ga::AttributeOwner::POINT:
            return pointAttributes_;
            break;
        case ga::AttributeOwner::VERTEX:
            return vertexAttributes_;
            break;
        case ga::AttributeOwner::PRIMITIVE:
            return primitiveAttributes_;
            break;
        case ga::AttributeOwner::GLOBAL:
            return globalAttributes_;
            break;
        default:
            throw std::runtime_error("Unexpected, owner could not be found");
    }
}


std::shared_ptr<ga::Attribute> geo::Geometry::getAttribByName(ga::AttributeOwner owner, std::string name)
{
    auto& vector = getAttributeStore(owner);
    for(auto it=vector.begin(); it!=vector.end(); ++it)
    {
        if((*it)->getName()==name)
        {
            return (*it);
        }
    }
    return nullptr;
}

