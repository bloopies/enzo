#include "Engine/Operator/OperatorTable.h"
#include <boost/dll/import.hpp>

#include <iostream>

void enzo::op::OperatorTable::addOperator(const char* internalName, const char* displayName, nt::opConstructor ctorFunc, prm::Template templates[])
{
    std::cout << "OPERATOR TABLE ADDED\n";
    std::cout << "adding operator: " << displayName << "\n";

    for(const prm::Template* t = templates; t->isValid(); ++t)
    {
        std::cout << "name: " << t->getName() << "\n";
    }

    enzo::op::OpInfo info {
        internalName,
        displayName,
        ctorFunc,
        templates,
    };

    opInfoStore_.push_back(info);
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

const std::optional<enzo::op::OpInfo> enzo::op::OperatorTable::getOpInfo(std::string name)
{
    for(auto it = opInfoStore_.begin(); it!=opInfoStore_.end(); ++it)
    {
        if(it->internalName==name)
        {
            return *it;
        }
    }
    return std::nullopt;
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
