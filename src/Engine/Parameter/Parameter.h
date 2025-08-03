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
    bt::floatT evalFloat(unsigned int index=0) const;
    bt::String evalString() const;
    enzo::prm::Type getType() const;
    
    void setFloat(bt::floatT value, unsigned int index=0);
    boost::signals2::signal<void ()> valueChanged;
private:
    Template template_;
    std::vector<bt::floatT> floatValues_;
    bt::String stringValue_ = "";

};
}
