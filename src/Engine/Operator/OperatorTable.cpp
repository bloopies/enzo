#include "Engine/Operator/OperatorTable.h"

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


std::vector<enzo::op::OpInfo> enzo::op::OperatorTable::opInfoStore_;
