#include "Engine/Operator/OperatorTable.h"

#include <iostream>

void enzo::op::OperatorTable::addOperator(nt::opConstructor ctorFunc)
{
    std::cout << "OPERATOR TABLE ADDED\n";
    // ctorFunc(5);
    ctorStore_.push_back(ctorFunc);
}

std::vector<enzo::nt::opConstructor> enzo::op::OperatorTable::ctorStore_;
