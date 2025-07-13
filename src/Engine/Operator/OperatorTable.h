#pragma once

#include <boost/config.hpp>
#include "Engine/Network/NetworkManager.h"

namespace enzo::op
{
class BOOST_SYMBOL_EXPORT OperatorTable
{
public:
    void addOperator(nt::opConstructor ctorFunc);
private:
    std::vector<nt::opConstructor> ctorStore_;
};
}
