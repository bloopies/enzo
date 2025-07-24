#pragma once
#include "Engine/Parameter/Template.h"
#include "Engine/Types.h"
#include <boost/signals2.hpp>

namespace enzo::prm
{
class Parameter
{
public:
    Parameter(Template prmTemplate);
    std::string getName() const;
    bt::floatT evalFloat() const;
    void setFloat(bt::floatT value);
    boost::signals2::signal<void ()> valueChanged;
private:
    Template template_;
    bt::floatT floatValue_ = 0;

};
}
