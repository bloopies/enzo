#pragma once

namespace enzo
{

    namespace ga
    {
        enum class AttributeOwner
        {
            POINT,
            VERTEX,
            PRIMITIVE,
            GLOBAL
        };
        enum class AttributeType
        {
            intT,
            floatT,
            listT,
            vectorT,
        };
        using AttrType = AttributeType;
        using AttrOwner = AttributeOwner;
    }
}
