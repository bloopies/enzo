#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"
#include <memory>
#include <stdexcept>
#include <optional>

using namespace enzo;


ga::Attribute::Attribute(std::string name, ga::AttributeType type)
: name_{name}, type_{type}
{
    // init store
    switch(type_)
    {
        case(AttrType::intT):
            intStore_=std::make_shared<std::vector<int>>();
            break;
        case(AttrType::floatT):
            floatStore_=std::make_shared<std::vector<float>>();
            break;
        case(AttrType::vectorT):
            vector3Store_=std::make_shared<std::vector<enzo::bt::Vector3>>();
            break;
        default:
            throw std::runtime_error("Type " + std::to_string(static_cast<int>(type_)) + " was not properly accounted for");

    }

}

ga::Attribute::Attribute(const Attribute& other)
{
    type_ = other.type_;
    private_= other.private_;
    hidden_ = other.hidden_;
    readOnly_ = other.readOnly_;
    name_ = other.name_;

    switch(type_)
    {
        case(AttrType::intT):
            intStore_=std::make_shared<std::vector<int>>(*other.intStore_);
            break;
        case(AttrType::floatT):
            floatStore_=std::make_shared<std::vector<float>>(*other.floatStore_);
            break;
        case(AttrType::vectorT):
            vector3Store_=std::make_shared<std::vector<enzo::bt::Vector3>>(*other.vector3Store_);
            break;
        default:
            throw std::runtime_error("Type " + std::to_string(static_cast<int>(type_)) + " was not properly accounted for");

    }
}


ga::AttributeType ga::Attribute::getType()
{
    return type_;
}

std::string ga::Attribute::getName()
{
    return name_;
}

