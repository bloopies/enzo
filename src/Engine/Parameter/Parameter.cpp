#include "Engine/Parameter/Parameter.h"
#include <iostream>


enzo::prm::Parameter::Parameter(Template prmTemplate)
: template_{prmTemplate}
{
    floatValue_ = prmTemplate.getDefault();
    std::cout << "created new parameter: " << prmTemplate.getName() << "\n";
}

std::string enzo::prm::Parameter::getName() const
{
    return template_.getName();
}

enzo::bt::floatT enzo::prm::Parameter::evalFloat() const
{
    return floatValue_;
}
void enzo::prm::Parameter::setFloat(bt::floatT value)
{
    floatValue_ = value;
}

