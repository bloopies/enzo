#include "Engine/Parameter/Template.h"
#include "Engine/Parameter/Type.h"

enzo::prm::Template::Template(enzo::prm::Type type, const char* name, bt::floatT theDefault, unsigned int vectorSize)
: type_{type}, name_{name}, default_{theDefault}, vectorSize_(vectorSize)
{
    
}

enzo::prm::Template::Template()
{
    
}

bool enzo::prm::Template::isValid() const
{
    return name_!=nullptr;

}

const enzo::prm::Type enzo::prm::Template::getType() const
{
    return type_;
}

const unsigned int enzo::prm::Template::getSize() const
{
    return vectorSize_;
}



const enzo::bt::floatT enzo::prm::Template::getDefault() const
{
    return default_;
}

const char* enzo::prm::Template::getName() const
{
    return name_;
}

