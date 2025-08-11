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
    enzo::prm::Type getType() const;

    bt::floatT evalFloat(unsigned int index=0) const;
    bt::String evalString(unsigned int index=0) const;
    bt::intT evalInt(unsigned int index=0) const;
    
    void setInt(bt::intT value, unsigned int index=0);
    void setFloat(bt::floatT value, unsigned int index=0);
    void setString(bt::String value, unsigned int index=0);

    boost::signals2::signal<void ()> valueChanged;
private:
    Template template_;
    std::vector<bt::floatT> floatValues_;
    std::vector<bt::String> stringValues_;
    std::vector<bt::intT> intValues_;

};
}
