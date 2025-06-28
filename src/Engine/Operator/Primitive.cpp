#include "Engine/Operator/Primitive.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"

enzo::Primitive::Primitive()
{

}

bool enzo::Primitive::addIntAttrib(AttributeOwner owner, AttributeInt attribute)
{
    bool status = true;

    switch(owner)
    {
        case enzo::AttributeOwner::POINT:
            pointAttribs_.push_back(attribute);
            break;
            

    }
    pointAttribs_.push_back(attribute);
    return status;
}
