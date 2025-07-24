#include "Engine/Parameter/Template.h"
#include "Engine/Parameter/Type.h"

enzo::prm::Template::Template(enzo::prm::Type type, const char* name, bt::floatT theDefault)
: type_{type}, name_{name}, default_{theDefault}
{
    
}

enzo::prm::Template::Template()
{
    
}

bool enzo::prm::Template::isValid() const
{
    return name_!=nullptr;

}

const enzo::bt::floatT enzo::prm::Template::getDefault() const
{
    return default_;
}

const char* enzo::prm::Template::getName() const
{
    return name_;
}

