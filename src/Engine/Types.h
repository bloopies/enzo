#pragma once
#include <Eigen/Dense>

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
    // basic types types
    namespace bt
    {
        using Vector3 = Eigen::Vector3d;
        using Vector4 = Eigen::Vector4d;
    }
    namespace nt
    {
        using OpId = uint64_t;

        enum class SocketIOType {
            Input,
            Output
        };

    }
}
