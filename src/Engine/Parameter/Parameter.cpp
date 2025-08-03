#include "Engine/Parameter/Parameter.h"
#include "Engine/Types.h"
#include <iostream>
#include <stdexcept>
#include <string>

enzo::prm::Parameter::Parameter(Template prmTemplate)
: template_{prmTemplate}
{
    floatValues_ = std::vector<bt::floatT>(prmTemplate.getSize(), prmTemplate.getDefault());
    std::cout << "created new parameter: " << prmTemplate.getName() << "\n";
}

std::string enzo::prm::Parameter::getName() const
{
    return template_.getName();
}

enzo::bt::floatT enzo::prm::Parameter::evalFloat(unsigned int index) const
{
    if(index >= floatValues_.size())
        throw std::out_of_range("Cannot access index: " + std::to_string(index) + " for parameter: " + getName());
    return floatValues_[index];
}

enzo::prm::Type enzo::prm::Parameter::getType() const
{
    return template_.getType();
}

enzo::bt::String enzo::prm::Parameter::evalString() const
{
    return stringValue_;
}

void enzo::prm::Parameter::setFloat(bt::floatT value, unsigned int index)
{
    std::cout << "accessing at: " << index << "\n";
    std::cout << "size: " << floatValues_.size() << "\n";
    floatValues_[index] = value;
    valueChanged();
}

