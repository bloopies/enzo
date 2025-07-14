#pragma once

#include <boost/config.hpp>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOpDef.h"

namespace enzo::op
{
class BOOST_SYMBOL_EXPORT OperatorTable
{
public:
    static void addOperator(nt::opConstructor ctorFunc);
    static nt::opConstructor getOpConstructor(size_t pos);
private:
    static std::vector<nt::opConstructor> ctorStore_;
};
}

