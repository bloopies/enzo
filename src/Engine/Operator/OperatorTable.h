#pragma once

#include <boost/config.hpp>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOpDef.h"
#include "Engine/Parameter/Template.h"


namespace enzo::op
{
struct OpInfo
{
    std::string internalName;
    std::string displayName;
    enzo::nt::opConstructor ctorFunc;
};

class BOOST_SYMBOL_EXPORT OperatorTable
{
public:
    static void addOperator(const char* internalName, const char* displayName, nt::opConstructor ctorFunc, prm::Template templateList[]);
    static nt::opConstructor getOpConstructor(std::string name);
    static std::vector<OpInfo> getData();
    // TODO: move to better spot (maybe engine class)
    static void initPlugins();
private:
    static std::vector<OpInfo> opInfoStore_;
};
using addOperatorPtr = void (*)(const char* internalName, const char* displayName, nt::opConstructor ctorFunc, prm::Template templateList[]);
}

