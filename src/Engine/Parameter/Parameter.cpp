#include "Engine/Parameter/Parameter.h"
#include <iostream>


enzo::prm::Parameter::Parameter(Template prmTemplate)
: template_{prmTemplate}
{
    std::cout << "created new parameter: " << prmTemplate.getName() << "\n";
}

std::string enzo::prm::Parameter::getName() const
{
    return template_.getName();
}

