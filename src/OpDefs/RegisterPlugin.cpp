#include "Engine/Operator/OperatorTable.h"
#include "GopHouse.h"
#include "OpDefs/GopTransform.hpp"
#include <boost/config.hpp>
#include <boost/dll.hpp>

extern "C"
{
    BOOST_SYMBOL_EXPORT void newSopOperator(enzo::op::addOperatorPtr addOperator)
    {
        addOperator(
            "transform",
            "Transform",
            &GopTransform::ctor,
            GopTransform::parameterList
        );
        addOperator(
            "house",
            "House",
            &GOP_house::ctor,
            GOP_house::parameterList
        );
    }

}
