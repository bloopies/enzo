#pragma once
#include "Engine/Parameter/Type.h"

namespace enzo::prm
{

class Template
{
public:
    Template(enzo::prm::Type type, const char* name);
private:
    enzo::prm::Type type_;
    // TODO: make a class that holds token and name
    const char* name_;

};

}

