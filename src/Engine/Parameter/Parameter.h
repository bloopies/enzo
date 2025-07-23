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
    inline bt::floatT evalFloat() const {return floatValue_;}
    inline void setFloat(bt::floatT value) {floatValue_ = value;}
private:
    Template template_;
    bt::floatT floatValue_ = 0;

};
}
