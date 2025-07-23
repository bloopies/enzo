#pragma once
#include "Engine/Parameter/Template.h"
#include "Engine/Types.h"

namespace enzo::prm
{
class FloatParm
{
public:
    FloatParm(Template prmTemplate);
    inline bt::floatT getValue() const {return value_;}
    inline void setValue(bt::floatT value) {value_ = value;}
private:
    Template template_;
    bt::floatT value_ = 0;

};
}
