#pragma once

#include <boost/config.hpp>
#include "Engine/Network/NetworkManager.h"

namespace enzo::op
{
class BOOST_SYMBOL_EXPORT OperatorTable
{
public:
    static void addOperator(nt::opConstructor ctorFunc);
private:
    static std::vector<nt::opConstructor> ctorStore_;
};
}

