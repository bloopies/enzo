#include "Engine/Operator/OperatorTable.h"
#include <boost/dll/import.hpp>

#include <iostream>

void enzo::op::OperatorTable::addOperator(const char* internalName, const char* displayName, nt::opConstructor ctorFunc)
{
    std::cout << "OPERATOR TABLE ADDED\n";
    std::cout << "adding operator: " << displayName << "\n";
    opInfoStore_.push_back({internalName, displayName, ctorFunc});
}

enzo::nt::opConstructor enzo::op::OperatorTable::getOpConstructor(std::string name)
{
    for(auto it = opInfoStore_.begin(); it!=opInfoStore_.end(); ++it)
    {
        if(it->internalName==name)
        {
            return it->ctorFunc;
        }
    }
    return nullptr;
}

std::vector<enzo::op::OpInfo> enzo::op::OperatorTable::getData()
{
    return opInfoStore_;
}

void enzo::op::OperatorTable::initPlugins()
{
    static bool pluginsLoaded=false;
    if(pluginsLoaded) return;

    auto initPlugin = boost::dll::import_symbol<void(enzo::op::addOperatorPtr)>(
        "build/src/OpDefs/libenzoOps1.so", "newSopOperator"
    );

    initPlugin(enzo::op::OperatorTable::addOperator);

    pluginsLoaded = true;
}

std::vector<enzo::op::OpInfo> enzo::op::OperatorTable::opInfoStore_;
