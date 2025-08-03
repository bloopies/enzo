#include "Engine/Parameter/Parameter.h"
#include "Engine/Parameter/Default.h"
#include "Engine/Types.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

enzo::prm::Parameter::Parameter(Template prmTemplate)
: template_{prmTemplate}
{
    floatValues_ = std::vector<bt::floatT>();
    floatValues_.reserve(prmTemplate.getSize());

    stringValues_ = std::vector<bt::String>(prmTemplate.getSize(), prmTemplate.getDefault().getString());
    stringValues_.reserve(prmTemplate.getSize());

    const unsigned int templateSize = prmTemplate.getSize();
    const unsigned int numDefaults = prmTemplate.getNumDefaults();

    if(numDefaults==1)
    {
        floatValues_ = std::vector<bt::floatT>(templateSize, prmTemplate.getDefault().getFloat());
        stringValues_ = std::vector<bt::String>(templateSize, prmTemplate.getDefault().getString());
    }

    for(int i=0; i<templateSize; ++i)
    {
        prm::Default prmDefault;
        if(i<numDefaults)
        {
             prmDefault = prmTemplate.getDefault(i);
        }
        floatValues_.push_back(prmDefault.getFloat());
        stringValues_.push_back(prmDefault.getString());
    }


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

enzo::bt::String enzo::prm::Parameter::evalString(unsigned int index) const
{
    if(index >= stringValues_.size())
        throw std::out_of_range("Cannot access index: " + std::to_string(index) + " for parameter: " + getName());
    return stringValues_[index];
}



enzo::prm::Type enzo::prm::Parameter::getType() const
{
    return template_.getType();
}


void enzo::prm::Parameter::setFloat(bt::floatT value, unsigned int index)
{
    if(index >= floatValues_.size())
        throw std::out_of_range("Cannot access index: " + std::to_string(index) + " for parameter: " + getName());
    floatValues_[index] = value;
    valueChanged();
}

void enzo::prm::Parameter::setString(bt::String value, unsigned int index)
{
    if(index >= stringValues_.size())
        throw std::out_of_range("Cannot access index: " + std::to_string(index) + " for parameter: " + getName());
    stringValues_[index] = value;
    valueChanged();
}
