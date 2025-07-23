#include "Engine/Parameter/Template.h"
#include "Engine/Parameter/Type.h"

enzo::prm::Template::Template(enzo::prm::Type type, const char* name)
: type_{type}, name_{name}
{
    
}

enzo::prm::Template::Template()
{
    
}

bool enzo::prm::Template::isValid() const
{
    return name_!=nullptr;

}

const char* enzo::prm::Template::getName() const
{
    return name_;
}

