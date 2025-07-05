#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include <iostream>
#include <memory>

enzo::nt::OpId enzo::nt::NetworkManager::addOperator()
{

    gopStore_.emplace(++maxOpId_, std::make_unique<GeometryOperator>());
    std::cout << "adding operator " << maxOpId_ << "\n";

    return maxOpId_;
}


enzo::nt::NetworkManager* enzo::nt::NetworkManager::getInstance()
{
    if(instancePtr_==nullptr)
    {
        instancePtr_ = new enzo::nt::NetworkManager();
    }
    return instancePtr_;
}

enzo::nt::GeometryOperator& enzo::nt::NetworkManager::getGeoOperator(nt::OpId opId)
{
    return *gopStore_.at(opId);
}

bool enzo::nt::NetworkManager::isValidOp(nt::OpId opId)
{
    auto it = gopStore_.find(opId);
    if( it == gopStore_.end() || it->second==nullptr )
    {
        return false;
    }
    return true;
}

void enzo::nt::NetworkManager::setDisplayOp(OpId opId)
{
    displayOp_=opId;
}

std::optional<enzo::nt::OpId> enzo::nt::NetworkManager::getDisplayOp()
{
    return displayOp_;
}

enzo::nt::NetworkManager* enzo::nt::NetworkManager::instancePtr_ = nullptr;

