#include "Engine/Parameter/Template.h"
#include "Engine/Parameter/Type.h"

enzo::prm::Template::Template(enzo::prm::Type type, const char* name)
: type_{type}, name_{name}
{
    
}
