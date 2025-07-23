#pragma once
#include "Engine/Parameter/Template.h"
#include "Engine/Types.h"

namespace enzo::prm
{
class Parameter
{
public:
    Parameter(Template prmTemplate);
    std::string getName() const;
    bt::floatT evalFloat() const;
    void setFloat(bt::floatT value);
private:
    Template template_;
    bt::floatT floatValue_ = 0;

};
}
