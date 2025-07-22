#pragma once
#include "Engine/Parameter/Type.h"

namespace enzo::prm
{

class Template
{
public:
    Template(enzo::prm::Type type);
private:
    enzo::prm::Type type_;

};

}

