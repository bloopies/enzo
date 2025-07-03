#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include <iostream>
#include <memory>

bool enzo::nt::NetworkManager::addOperator()
{

    gopStore_.emplace(++maxOpId_, std::make_unique<GeometryOperator>());
    std::cout << "adding operator\n";

    return true;
}

