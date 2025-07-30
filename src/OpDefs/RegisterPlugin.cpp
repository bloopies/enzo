#include "Engine/Operator/OpInfo.h"
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
            enzo::op::OpInfo {
                "transform",
                "Transform",
                &GopTransform::ctor,
                GopTransform::parameterList,
                1,
                1,
                1,
            }
        );
        addOperator(
            enzo::op::OpInfo {
                "house",
                "House",
                &GOP_house::ctor,
                GOP_house::parameterList,
                0,
                0,
                1,
            }
        );
    }

}
