#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include <iostream>
#include <memory>
#include <stack>
#include <algorithm>

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
    getTraversalGraph(opId);
}

void enzo::nt::NetworkManager::cookOp(enzo::nt::OpId opId)
{
    std::cout << "COOKING: " << opId << "\n";
}

std::vector<enzo::nt::OpId> enzo::nt::NetworkManager::getTraversalGraph(enzo::nt::OpId opId)
{
    std::stack<enzo::nt::OpId> traversalBuffer;
    std::vector<enzo::nt::OpId> traversalGraph;
    traversalBuffer.push(opId);

    while(traversalBuffer.size()!=0)
    {
        enzo::nt::OpId currentOp = traversalBuffer.top();
        std::cout << "cooking node: " << currentOp << "\n";
        traversalBuffer.pop();
        auto inputConnections = getGeoOperator(currentOp).getInputConnections();
        for(auto connection : inputConnections)
        {
            traversalBuffer.push(connection->getInputOpId());
            traversalGraph.push_back(connection->getInputOpId());
        }
    }

    std::reverse(traversalGraph.begin(), traversalGraph.end());
    return traversalGraph;
}


std::optional<enzo::nt::OpId> enzo::nt::NetworkManager::getDisplayOp()
{
    return displayOp_;
}

enzo::nt::NetworkManager* enzo::nt::NetworkManager::instancePtr_ = nullptr;

