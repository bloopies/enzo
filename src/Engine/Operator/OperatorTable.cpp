#include "Engine/Operator/OperatorTable.h"

#include <iostream>

void enzo::op::OperatorTable::addOperator(const char* internalName, const char* displayName, nt::opConstructor ctorFunc)
{
    std::cout << "OPERATOR TABLE ADDED\n";
    std::cout << "adding operator: " << displayName << "\n";
    ctorStore_.push_back(ctorFunc);
}

enzo::nt::opConstructor enzo::op::OperatorTable::getOpConstructor(size_t pos)
{
    return ctorStore_.at(pos);
}

std::vector<enzo::nt::opConstructor> enzo::op::OperatorTable::ctorStore_;
